#include "snake.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "wall.h" // Task: Wall

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  float new_x;
  float new_y;
  switch (direction) {
    case Direction::kUp:
      new_y = head_y - speed;
      break;

    case Direction::kDown:
      new_y = head_y + speed;
      break;

    case Direction::kLeft:
      new_x = head_x - speed;
      break;

    case Direction::kRight:
      new_x = head_x + speed;
      break;
  }

  // // Wrap the Snake around to the beginning if going off of the screen.
  // head_x = fmod(head_x + grid_width, grid_width);
  // head_y = fmod(head_y + grid_height, grid_height);
  switch (direction) {
    case Direction::kUp:
      // If a snake head is already out of the border 
      // OR the new head position isn't occupied by itself.
      if (head_y <= 0)
        {
          // turn = true;
          // at upper left corner
          if (head_x <= 0 && SnakeCell(head_x + speed, head_y)) {
            direction = Direction::kRight;
            new_x = head_x + speed;
            new_y = head_y;
          }
          else {
            direction = Direction::kLeft;
            new_x = head_x - speed;
            new_y = head_y;
          }
        }
      break;

    case Direction::kDown:
      if (head_y >= grid_height - speed)
          {
            // turn = true;
            // at bottom right corner
            if (head_x >= grid_width - speed && SnakeCell(head_x - speed, head_y)) {
              direction = Direction::kLeft;
              new_x = head_x - speed;
              new_y = head_y;
            }
            else {
              direction = Direction::kRight;
              new_x = head_x + speed;
              new_y = head_y;
            }
          }
        break;

    case Direction::kRight:
        // If a snake head is already out of the border 
        // OR the new head position isn't occupied by itself.
        if (head_x >= grid_width - speed)
          {
            // turn = true;
            // at upper right corner
            if (head_y <= 0 && SnakeCell(head_x, head_y + speed)) {
              direction = Direction::kDown;
              new_x = head_x;
              new_y = head_y + speed;
            }
            else {
              direction = Direction::kUp;
              new_x = head_x;
              new_y = head_y - speed;
            }
          }
        break;

    case Direction::kLeft:
        if (head_x <= 0)
          {
            // turn = true;
            // at bottom left corner
            if (head_x >= grid_height - speed && SnakeCell(head_x, head_y - speed)) {
              direction = Direction::kUp;
              new_x = head_x;
              new_y = head_y - speed;
            }
            else {
              direction = Direction::kDown;
              new_x = head_x;
              new_y = head_y - speed;
            }
          }
        break;
  }

  head_x = new_x;
  head_y = new_y;
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }

  // Task: Wall
  for (auto const &point : wall.getWall()) {
    if (current_head_cell.x == point.x && current_head_cell.y == point.y) {
      alive = false;
    }
  } 
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}