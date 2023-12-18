#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

// Structure to hold key states
typedef struct {
    int up;
    int down;
    int left;
    int right;
} KeyState;

void handle_input(SDL_Event event, KeyState *keyState);

#endif
