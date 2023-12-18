#include "player.h"
#include <SDL.h>
#include "input.h"
#include "image_loader.h"
#include "collision.h"
#include "world.h"
#include "graphics.h"
#include "enemy.h"
#include "math.h"

static SDL_Texture* imageTexture = NULL;
static Player player = {512, 240};
static float moveSpeed = 250.0f; // Pixels per second
static SDL_Renderer* renderer = NULL;

SDL_Rect* get_player_box() {
    static SDL_Rect playerBox;
    playerBox.x = player.x;
    playerBox.y = player.y;
    playerBox.w = 32;
    playerBox.h = 64;
    return &playerBox;
}

void load_player_texture() {
    renderer = get_renderer();
    imageTexture = load_image("./assets/images/kid.png", renderer);
}

void reset_player() {
    player.x = 512;
    player.y = 240;
}

void update_player(float delta, KeyState* keyState, char worldMatrix[][WORLD_WIDTH]) {
    int newplayerX = player.x;
    int newplayerY = player.y;

    // Update position based on key states
    if (keyState->up) newplayerY -= (int)(moveSpeed * delta);
    if (keyState->down) newplayerY += (int)(moveSpeed * delta);
    if (keyState->left) newplayerX -= (int)(moveSpeed * delta);
    if (keyState->right) newplayerX += (int)(moveSpeed * delta);

    // Handle collisions separately for X and Y
    player.x = check_collision_x(newplayerX, player.x, player.y, 32, 64, worldMatrix);
    player.y = check_collision_y(player.x, newplayerY, player.y, 32, 64, worldMatrix);

    // Screen wrapping
    player.x = (player.x + WIDTH) % WIDTH;
    player.y = (player.y + HEIGHT) % HEIGHT;
}

void render_player() {
    draw_image(renderer, imageTexture, player.x - 16, player.y);
}

int get_is_player_hit() {
    SDL_Rect playerBox = {player.x, player.y, 32, 64};
    int num_enemenies = get_num_enemies();
    Enemy* enemies = get_enemies();
    for (int i = 0; i < num_enemenies; i++) {
        if (enemies[i].isActive && SDL_HasIntersection(&playerBox, &enemies[i].position)) {
            return 1;
        }
    }
    return 0;
}
