#include "image_loader.h"
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* load_image(const char* file, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(file);
    if (!surface) {
        printf("Error loading image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
    }

    return texture;
}

void draw_image(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}
