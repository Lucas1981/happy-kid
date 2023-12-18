#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "input.h"
#include "world.h"

// Player structure
typedef struct {
    int x;
    int y;
} Player;

// Function prototypes
void load_player_texture();
void update_player(float delta, KeyState* keyState, char worldMatrix[][WORLD_WIDTH]);
void render_player();
void reset_player();
int get_is_player_hit();
SDL_Rect* get_player_box();

#endif
