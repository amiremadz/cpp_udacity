#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include<mutex>
#include<thread>
#include <iostream>
#include <future>

class Wall {

public:

  enum class WallDirection { kForeward, kBackward };

  Wall(std::size_t grid_width, std::size_t grid_height);
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

  int limit;
  int _wallLength = 4;
  float _wallSpeed {0.1f};

  WallDirection _wallDirection = WallDirection::kForeward;

  std::mutex _mutex;
  std::thread update_thread;
  std::promise<void> exitThread;
  std::future<void> futureThreadobj;
};

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller  &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  

 private:
  Snake snake;
  Wall wall;// = std::make_unique<Wall>();
  SDL_Point food;
  bool running = true;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif