#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WIDTH 640
#define HEIGHT 512

#include <SDL.h>

SDL_Renderer* get_renderer();

// Function to initialize the renderer
int init_graphics();
void cleanup_graphics();

#endif
