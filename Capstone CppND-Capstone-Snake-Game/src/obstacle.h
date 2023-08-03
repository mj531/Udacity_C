#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Obstacle {
 public:
  Obstacle(std::size_t grid_width, std::size_t grid_height)
      :grid_width{grid_width}, grid_height{grid_height}
  {
      createObstacle();
  }
  
  std::vector <SDL_Point> getObstacle();

 private:
  void createObstacle();
  std::vector <SDL_Point> _SDLPoints;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif