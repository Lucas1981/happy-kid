#include "input.h"

void handle_input(SDL_Event event, KeyState *keyState) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT: keyState->left = 1; break;
            case SDLK_RIGHT: keyState->right = 1; break;
            case SDLK_UP: keyState->up = 1; break;
            case SDLK_DOWN: keyState->down = 1; break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT: keyState->left = 0; break;
            case SDLK_RIGHT: keyState->right = 0; break;
            case SDLK_UP: keyState->up = 0; break;
            case SDLK_DOWN: keyState->down = 0; break;
        }
    }
}
