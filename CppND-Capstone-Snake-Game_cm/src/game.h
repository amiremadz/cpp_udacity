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

#include "wall.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int difficulty);
  ~Game();
  void Run(Controller  &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetMoves() const;
  

 private:
  Snake snake;
  Wall wall;// = std::make_unique<Wall>();
  SDL_Point food;
  bool running = true;
  int moves {0};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif