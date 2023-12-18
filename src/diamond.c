#include "diamond.h"
#include "image_loader.h" // For load_image function
#include <stdio.h>
#include "player.h"
#include "graphics.h"
#include "sound.h"

// Global texture for all diamonds
static SDL_Texture* diamondTexture = NULL;
static Diamond* diamonds = NULL;
static int numDiamonds = 0;
static SDL_Renderer* renderer = NULL;

static void load_diamond_texture() {
    diamondTexture = load_image("./assets/images/diamond.png", renderer);
}

void init_diamonds() {
    renderer = get_renderer();
    // Load diamond texture if not already loaded
    if (!diamondTexture) {
        load_diamond_texture();
    }

    // Open the file
    FILE* file = fopen("./assets/diamonds.txt", "r");
    if (!file) {
        perror("Error opening diamonds.txt");
        return;
    }

    // Read the number of diamonds
    fscanf(file, "%d", &numDiamonds);

    // Allocate memory for diamonds
    if (diamonds == NULL) {
        diamonds = malloc(numDiamonds * sizeof(Diamond));
    }

    // Read coordinates for each diamond
    for (int i = 0; i < numDiamonds; i++) {
        int x, y;
        fscanf(file, "%d %d", &x, &y);
        (diamonds)[i].texture = diamondTexture;
        (diamonds)[i].position = (SDL_Rect){x, y, 32, 32}; // Assuming size is 32x32
        (diamonds)[i].state = AVAILABLE;
    }

    fclose(file);
}

void render_diamonds() {
    for (int i = 0; i < numDiamonds; i++) {
        if (diamonds[i].state == AVAILABLE) {
            SDL_RenderCopy(renderer, diamonds[i].texture, NULL, &diamonds[i].position);
        }
    }
}

void update_diamonds() {
    SDL_Rect* playerBox = get_player_box();
    for (int i = 0; i < numDiamonds; i++) {
        if (diamonds[i].state == AVAILABLE && SDL_HasIntersection(playerBox, &diamonds[i].position)) {
            play_sound(DIAMOND);
            diamonds[i].state = COLLECTED;
        }
    }
}

int get_count_available_diamonds() {
    int count = 0;
    for (int i = 0; i < numDiamonds; i++) {
        if (diamonds[i].state == AVAILABLE) {
            count++;
        }
    }
    return count;
}

void free_diamonds() {
    free(diamonds);
}
