#include "obstacle.h"
#include <iostream>
#include "SDL.h"

void Obstacle::createObstacle()
{
    SDL_Point point;
    for (int i=0; i<grid_width/2; i++)
    {
        point.x = i+(grid_width/4);
        point.y = grid_height/3;
        _SDLPoints.emplace_back(point);
    }
}

std::vector <SDL_Point> Obstacle::getObstacle()
{
    return _SDLPoints;
}