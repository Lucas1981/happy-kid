#ifndef DIAMOND_H
#define DIAMOND_H

#include <SDL.h>

// Diamond states
typedef enum {
    AVAILABLE,
    COLLECTED
} DiamondState;

// Diamond structure
typedef struct {
    SDL_Rect position; // Contains x, y, width, and height
    DiamondState state;
    SDL_Texture* texture; // Texture for the diamond image
} Diamond;

void init_diamonds();
void render_diamonds();
void update_diamonds();
void free_diamonds();
int get_count_available_diamonds();

#endif
