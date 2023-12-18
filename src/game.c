#include <SDL.h>
#include "image_loader.h"
#include "graphics.h"
#include "world.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "diamond.h"
#include "input.h"
#include "user_interface.h"
#include "game.h"
#include "sound.h"

static SDL_Renderer* renderer;
static Uint32 lastTime, currentTime;
static KeyState keyState = {0, 0, 0, 0};
static int init_graphics_success;
static float delta;
GameState game_state = BEFORE_PLAY;

GameState get_game_state() {
    return game_state;
}

void set_game_state(GameState new_game_state) {
    game_state = new_game_state;
}

int init_game() {
    printf("Starting app...\n");
    init_graphics_success = init_graphics();

    if (!init_graphics_success) {
        printf("Failed to initialize graphics!\n");
        return 1;
    }

    printf("Initializing...\n");

    initiate_user_interface();
    init_world();
    load_player_texture();
    init_enemies();
    init_diamonds();
    init_sounds();

    renderer = get_renderer();
    lastTime = SDL_GetTicks();

    return 0;
}

void reset_game() {
    reset_player();
    reset_enemies();
    init_diamonds();
}

void game_action(int update_actors) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            set_game_state(QUIT);
        } else {
            handle_input(event, &keyState);
        }
    }
    
    currentTime = SDL_GetTicks();
    Uint32 deltaTime = currentTime - lastTime;
    delta = (float)deltaTime / 1000.0f; // Delta time in seconds
    lastTime = currentTime;
    int available_diamonds_count;

    if (update_actors) {
        update_player(delta, &keyState, worldMatrix);
        update_diamonds();
        update_enemies(deltaTime, worldMatrix);

        available_diamonds_count = get_count_available_diamonds();
        int is_player_hit = get_is_player_hit();

        if (is_player_hit) {
            play_sound(DEATH);
            set_game_state(HIT);
        } else if (available_diamonds_count == 0) {
            set_game_state(WON);
        }
    }
    
    // Clear screen with black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_world();
    render_diamonds();
    render_enemies();
    render_player();
}

void cleanup_game() {
    printf("Cleaning up...\n");

    // Cleanup
    cleanup_graphics();    
    cleanup_user_interface();
    free_diamonds();
    free_enemies();
    cleanup_sounds();
}
