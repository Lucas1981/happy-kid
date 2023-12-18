#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <SDL.h>

// Function to load an image into a texture
SDL_Texture* load_image(const char* file, SDL_Renderer* renderer);

// Function to draw an image at a specified position
void draw_image(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

#endif
