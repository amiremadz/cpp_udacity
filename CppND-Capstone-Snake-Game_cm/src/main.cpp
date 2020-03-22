#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <thread>
#include <chrono>
#include <limits>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640}; //640
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  int difficulty {0};
  bool acceptable = false;

  std::cout << "Choose Difficulty level(integer) - 1 (easy) <==> 5 (hard): \n";
  std::cin >> difficulty;

    
   if (difficulty > 0 && difficulty < 6) acceptable = true;

   else
    while(acceptable == false || !(std::cin >> difficulty))
      {
      std::cin.clear();                                                               //functionality to block non integers
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input, please try entering difficulty again: \n";
      std::cin >> difficulty;
      if (difficulty > 0 &&  difficulty < 6) 
      {
        acceptable = true;
        break;
      }
      }
   

  std::cout << "Difficulty chosen: " << difficulty << "\n";

  std::cout << "Game will begin in: \n";

  for (int i = 3; i > 0; i --)
  {
    std::cout << i << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, 6 - difficulty);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Score: " << game.GetScore() << ". With " << game.GetMoves() << " moves. \n";

  if(game.GetScore() != 0) std::cout << "Moves to Score Ratio= ~ " << game.GetMoves()/game.GetScore() << ":1. \n";
  
  return 0;
}