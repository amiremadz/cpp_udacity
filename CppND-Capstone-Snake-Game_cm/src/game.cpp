#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <thread>
#include <future>


Wall::Wall(std::size_t grid_width, std::size_t grid_height) :
 _wallSeed_x(grid_width /2 - 2),
  _wallSeed_y(grid_height/2), limit(grid_width) {

  std::cout << "Wall Constructor" << "\n";
  //std::cout<< "Wall size:" << wall.size() << "\n";

  for (int i = 0; i < _wallLength; i ++)    //SDL_Point  &point : wall
    {
      SDL_Point block{
      static_cast<int>(_wallSeed_x) + i,
      static_cast<int>(_wallSeed_y)};
      _wall.push_back(block);
    }
  //std::cout<< "Wall size:" << _wall.size() << "\n";
}

void Wall::ChangeDirection()
{
  switch (_wallDirection)  {
    case WallDirection::kForeward:
    _wallDirection = WallDirection::kBackward;
    break;

    case WallDirection::kBackward:
    _wallDirection = WallDirection::kForeward;
    break;
  }
}

void Wall::UpdateWall()
{
  _wall[0].x = static_cast<int>(_wallSeed_x);
  for (int i = 1; i < _wallLength; i ++)  
  {
  _wall[i].x = _wallSeed_x + i;
  //std::cout << "Wall i.x: " << _wall[i].x << "\n";
  }
}

void Wall::MoveWall()
{
  //while(true) {

    //std::cout << "Moving Wall thread: "<< _wallSeed_x << "\n"; 
    switch (_wallDirection) {

      case WallDirection::kForeward:
      if (_wallSeed_x + 4 < limit) _wallSeed_x += _wallSpeed; 
      else
      {
          ChangeDirection();
          _wallSeed_x -= _wallSpeed;
      }
      break;

      case WallDirection::kBackward:
      if (_wallSeed_x > 0) _wallSeed_x -= _wallSpeed;
      else
      {
        {
          ChangeDirection();
          _wallSeed_y += _wallSpeed;
        }
      }
    }

    //std::this_thread::sleep_for(std::chrono::milliseconds(20));
    UpdateWall();

  //}
}

std::vector<SDL_Point> Wall::GetWallCord()
{
  return _wall;
}

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      wall(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {

  PlaceFood();
}

void Game::Run(Controller  &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {

    wall->MoveWall();

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    int moves = controller.GetKeyMove();
    Update();
    renderer.Render(snake, food, wall->GetWallCord());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, moves);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::Update() {
  if (!snake.alive) return;


  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }