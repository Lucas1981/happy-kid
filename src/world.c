#include "world.h"
#include "image_loader.h"
#include <stdio.h>
#include "graphics.h"

// Tile textures
static SDL_Texture* brickTexture = NULL;
static SDL_Texture* floorTexture = NULL;
static SDL_Renderer* renderer = NULL;

// World matrix
char worldMatrix[WORLD_HEIGHT][WORLD_WIDTH];

void init_world() {
    renderer = get_renderer();
    brickTexture = load_image("./assets/images/brick.png", renderer);
    floorTexture = load_image("./assets/images/floor.png", renderer);

    // Load the world from file
    FILE *file = fopen("./assets/world.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            char tileType = fgetc(file);
            if (tileType == '\n') { // Skip new line character
                tileType = fgetc(file);
            }
            worldMatrix[i][j] = tileType;
        }
    }
    fclose(file);
}

void render_world() {
    int tileSize = 64; // Tile size in pixels
    for (int i = 0; i < WORLD_HEIGHT; ++i) {
        for (int j = 0; j < WORLD_WIDTH; ++j) {
            SDL_Texture* currentTexture = NULL;
            switch (worldMatrix[i][j]) {
                case TILE_BRICK:
                    currentTexture = brickTexture;
                    break;
                case TILE_FLOOR:
                    currentTexture = floorTexture;
                    break;
            }
            if (currentTexture) {
                draw_image(renderer, currentTexture, j * tileSize, i * tileSize);
            }
        }
    }
}
