#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <thread>
#include <future>


Wall::Wall(std::size_t grid_width, std::size_t grid_height) :
 _wallSeed_x(grid_width /2 - 10),
  _wallSeed_y(grid_height/2), limit(grid_width) {

  std::cout << "Wall Constructor" << "\n";

  for (int i = 0; i < _wallLength; i ++)  
    {
      SDL_Point block{
      static_cast<int>(_wallSeed_x) + i,
      static_cast<int>(_wallSeed_y)};
      _wall.push_back(block);
    }
  //std::cout<< "Wall size:" << _wall.size() << "\n";
}

void Wall::KillThread()
{
  std::cout << "Killing thread \n";
  isOperating = false;
  //exitThread.set_value();
  update_thread.join();
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
  //futureThreadobj = exitThread.get_future();
  //update_thread = std::thread(&Wall::MoveWall, std::ref(futureThreadobj));
  update_thread = std::thread(&Wall::MoveWall, this);
}

void Wall::MoveWall()
{

  //int counter = 0;

  while(isOperating ==true) {

    std::lock_guard<std::mutex> lck(_mutex);

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
          _wallSeed_x += _wallSpeed;
        }
      }
    }

    _wall[0].x = static_cast<int>(_wallSeed_x);

    for (int i = 1; i < _wallLength; i ++)  
    {
    _wall[i].x = _wallSeed_x + i;
    }


    //std::cout << "Moving Wall Iteration #: " << counter << "\n";
    //counter +=1;

    std::this_thread::sleep_for(std::chrono::milliseconds(5));    //Delay to control speed of wall moving, also helps with thread data access

  }
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

Game::~Game(){};

void Game::Run(Controller  &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  //bool running = true;

  wall.UpdateWall();  //initiate thread to constantly move wall back and fourth
  

  while (running) {


    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    int moves = controller.GetKeyMove();
    Update();
    renderer.Render(snake, food, wall.GetWallCord());

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

    if(!snake.alive) running = false;
  }
  wall.KillThread();
 
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && x < 32 && y < 32) {
      food.x = x;
      food.y = y;
      std::cout<< "Food (x,y): (" << food.x <<", " << food.y << ")\n";
      return;
    }
  }
}


void Game::Update() {
  

  for (auto const &block : wall.GetWallCord())        //check to see if the snake's body hit the wall, if so the game is over
    {
      for (auto const &item : snake.body)
      {
        //std::cout<< "wall (x,y): (" << block.x <<", " << block.y << ")\n";
        //std::cout<< "snake (x,y): (" << item.x <<", " << item.y << ")\n";
        if(block.x == item.x && block.y == item.y) 
        {
          snake.alive = false;
        }
      }

      std::cout<< "wall (x,y): (" << block.x <<", " << block.y << ")\n";
      std::cout<< "snake head (x,y): (" << static_cast<int>(snake.head_x) <<", " << static_cast<int>(snake.head_y) << ")\n";
      if (block.x == static_cast<int>(snake.head_x) && block.y == static_cast<int>(snake.head_y)) //check to see if snake's head hit the wall
      {
        snake.alive = false;
      }
    }

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