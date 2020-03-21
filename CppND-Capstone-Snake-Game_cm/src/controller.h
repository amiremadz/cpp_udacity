#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller {
 public:

  void HandleInput(bool &running, Snake &snake) ;
  int GetKeyMove(){return *key_moves.get();}
  

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  std::unique_ptr<int> key_moves = std::make_unique<int>();
};

#endif