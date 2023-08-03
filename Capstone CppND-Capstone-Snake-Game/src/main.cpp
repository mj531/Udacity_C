#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "obstacle.h" // Task: Obstacle


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{240}; //from 640 to 240
  constexpr std::size_t kScreenHeight{240};
  constexpr std::size_t kGridWidth{10}; //from 32 to 10
  constexpr std::size_t kGridHeight{10};

  Obstacle obstacle(kGridWidth, kGridHeight); // Task: Obstacle

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth,
                    kGridHeight, obstacle); // Task: Obstacle
  Controller controller;
  Game game(kGridWidth, kGridHeight, obstacle); // Task: Obstacle
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}