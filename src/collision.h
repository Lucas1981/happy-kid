#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include "world.h" // Include this to get WORLD_WIDTH and WORLD_HEIGHT

// Function to check for X-axis collision and adjust X position
int check_collision_x(int proposedX, int currentX, int currentY, int width, int height, char worldMatrix[][WORLD_WIDTH]);

// Function to check for Y-axis collision and adjust Y position
int check_collision_y(int currentX, int proposedY, int currentY, int width, int height, char worldMatrix[][WORLD_WIDTH]);

#endif
