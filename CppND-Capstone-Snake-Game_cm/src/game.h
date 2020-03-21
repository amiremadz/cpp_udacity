#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Wall {

public:

  enum class WallDirection { kForeward, kBackward };

  Wall(std::size_t grid_width, std::size_t grid_height);
  void MoveWall();
  void ChangeDirection();
  void UpdateWall();

  std::vector<SDL_Point> GetWallCord();
  //std::vector<SDL_Point> _wall;

private:
  std::vector<SDL_Point> _wall;
  float _wallSeed_x;
  float _wallSeed_y;
  int limit;
  int _wallLength = 4;
  float _wallSpeed {0.1f};
  WallDirection _wallDirection = WallDirection::kForeward;
};

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller  &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  

 private:
  Snake snake;
  std::unique_ptr<Wall> wall;// = std::make_unique<Wall>();
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif