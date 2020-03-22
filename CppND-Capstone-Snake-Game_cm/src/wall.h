#ifndef WALL_H
#define WALL_H


#include<mutex>
#include<thread>
#include <iostream>
#include <future>
#include<vector>
#include "SDL.h"

class Wall {

public:

  enum class WallDirection { kForeward, kBackward };

  Wall(std::size_t grid_width, std::size_t grid_height, int challenge);
  void KillThread();
  void MoveWall();
  void ChangeDirection();
  void UpdateWall();

  std::vector<SDL_Point> GetWallCord();
  //std::vector<SDL_Point> _wall;

private:
  std::vector<SDL_Point> _wall;
  float _wallSeed_x;
  float _wallSeed_y;
  bool isOperating = true;
  int difficulty {0};

  int limit;
  int _wallLength = 4;
  float _wallSpeed {0.1f};

  WallDirection _wallDirection = WallDirection::kForeward;

  std::mutex _mutex;
  std::thread update_thread;
  std::promise<void> exitThread;
  std::future<void> futureThreadobj;
};

#endif