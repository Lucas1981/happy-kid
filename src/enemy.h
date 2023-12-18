#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "world.h"
#include "animation.h"

typedef struct {
    SDL_Rect position;
    Animation animation;
    int directionX;
    int directionY;
    int isActive; // Flag to indicate if the enemy is active
} Enemy;

// Initialize enemies
void init_enemies();

// Update enemies
void update_enemies(Uint32 deltaTime, char worldMatrix[][WORLD_WIDTH]);

// Render enemies
void render_enemies();

// Reset enemies
void reset_enemies();

// Get number of enemies
int get_num_enemies();

// Get enemies
Enemy* get_enemies();

// Free enemy resources
void free_enemies();

#endif
