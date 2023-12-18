#include "game.h"
#include <SDL.h>
#include "user_interface.h"
#include "graphics.h"
#include "diamond.h"

int main(int argc, char* argv[]) {
    Uint32 stateTimer = SDL_GetTicks(); // Timer to track state duration    
    int init_success = init_game();
    char buffer[64];
    int available_diamonds_count;
    
    if (init_success == 1) {
        printf("Failed to initialize game!\n");
        return 1;
    }

    GameState gameState = get_game_state();
    GameState prevGameState = gameState;
    SDL_Renderer* renderer = get_renderer();

    printf("Start game!\n");

    while (gameState != QUIT) {
        game_action(gameState == PLAYING);

        gameState = get_game_state();

        if (prevGameState != gameState) {
            // Game state changed, so we should reset the timer
            stateTimer = SDL_GetTicks();
            prevGameState = gameState;
        }

        switch (gameState) {
            case BEFORE_PLAY: // 0
                if (SDL_GetTicks() - stateTimer > 2000) { // 2 seconds
                    set_game_state(PLAYING);
                } else {
                    // Render "READY?" message
                    print_user_interface_with_outline(renderer, "READY?", 320, 200);
                }
                break;

            case HIT:
                if (SDL_GetTicks() - stateTimer > 2000) {
                    reset_game();
                    set_game_state(BEFORE_PLAY);
                } else {
                    // Render "YOU DIED" message
                    print_user_interface_with_outline(renderer, "YOU DIED", 320, 200);
                }
                break;

            case WON:
                if (SDL_GetTicks() - stateTimer > 2000) {
                    reset_game();
                    set_game_state(BEFORE_PLAY);
                } else {
                    // Render "YOU WON!" message
                    print_user_interface_with_outline(renderer, "YOU WON!", 320, 200);
                }
                break;

            case PLAYING:
                available_diamonds_count = get_count_available_diamonds();
                sprintf(buffer, "number of diamonds = %i", available_diamonds_count);
                print_user_interface_with_outline(renderer, buffer, 10, 10);
                break;

            case QUIT:
                break;

            default:
                printf("Unknown value for gameState\n");
                return 1;
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    cleanup_game();

    printf("Goodbye!\n");

    return 0;
}


