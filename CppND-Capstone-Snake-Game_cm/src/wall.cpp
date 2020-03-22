#include "SDL.h"
#include "wall.h"
#include <chrono>
#include <thread>
#include <future>


Wall::Wall(std::size_t grid_width, std::size_t grid_height, int challenge) :
 _wallSeed_x(grid_width /2 - 10),
  _wallSeed_y(grid_height/2), limit(grid_width),
  difficulty(challenge) {

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

    //std::cout << "Difficulty: " << difficulty << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(difficulty));    //Delay to control speed of wall moving, also helps with thread data access

  }
}

std::vector<SDL_Point> Wall::GetWallCord()
{
  return _wall;
}
