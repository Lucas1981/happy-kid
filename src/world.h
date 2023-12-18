#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>

// Tile type constants
#define TILE_BRICK 'B'
#define TILE_FLOOR 'F'

// World matrix dimensions
#define WORLD_WIDTH 10
#define WORLD_HEIGHT 8

// World matrix declaration
extern char worldMatrix[WORLD_HEIGHT][WORLD_WIDTH];

// Initialize the world
void init_world();

// Render the world
void render_world();

#endif
