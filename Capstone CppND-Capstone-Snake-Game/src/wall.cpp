#include "wall.h"
#include <iostream>
#include "SDL.h"

void Wall::createWall()
{
    SDL_Point point;
    for (int i=0; i<grid_width/4; i++)
    {
        point.x = i+(grid_width/8);
        point.y = grid_height/4;
        _SDLPoints.emplace_back(point);
    }
}

std::vector <SDL_Point> Wall::getWall()
{
    return _SDLPoints;
}