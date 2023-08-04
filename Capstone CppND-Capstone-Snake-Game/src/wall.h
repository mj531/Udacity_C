#ifndef WALL_H
#define WALL_H

#include <vector>
#include "SDL.h"


class Wall {
 public:
  Wall(std::size_t grid_width, std::size_t grid_height)
      :grid_width{grid_width}, grid_height{grid_height}
  {
      createWall();
  }
  
  std::vector <SDL_Point> getWall();

 private:
  void createWall();
  std::vector <SDL_Point> _SDLPoints;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif