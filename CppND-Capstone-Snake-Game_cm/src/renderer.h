#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, std::vector<SDL_Point> const wall);
  void UpdateWindowTitle(int score, int fps, int moves);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  //SDL_Window *sdl_window_2;
  //SDL_Renderer *sdl_renderer_2;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif