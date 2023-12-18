#include "collision.h"
#include "world.h" // For WORLD_WIDTH, TILE_BRICK and TILE_FLOOR
#include "math.h"

int check_collision_x(int proposedX, int currentX, int currentY, int width, int height, char worldMatrix[][WORLD_WIDTH]) {
    SDL_Rect playerBox = { proposedX, currentY, width, height }; // Player hitbox

    int start_x = floor(proposedX / 64);
    int stop_x = start_x + 1;
    int start_y = floor(currentY / 64);
    int stop_y = start_y + 1;
    int padding = (64 - width) / 2;

    for (int i = start_y; i <= stop_y; ++i) {
        for (int j = start_x; j <= stop_x; ++j) {
            if (worldMatrix[i][j] == TILE_BRICK) {
                SDL_Rect brickBox = { j * 64, i * 64, 64, 64 };
                if (SDL_HasIntersection(&playerBox, &brickBox)) {
                    if (proposedX > currentX) {
                        // Moving right; place the player to the left of the brick
                        return brickBox.x - playerBox.w;
                    } else {
                        // Moving left; place the player to the right of the brick
                        return brickBox.x + brickBox.w;
                    }
                }
            }
        }
    }

    return proposedX; // No collision
}

int check_collision_y(int currentX, int proposedY, int currentY, int width, int height, char worldMatrix[][WORLD_WIDTH]) {
    SDL_Rect playerBox = { currentX, proposedY, width, height }; // Player hitbox

    int start_x = floor(currentX / 64);
    int stop_x = start_x + 1;
    int start_y = floor(proposedY / 64);
    int stop_y = start_y + 1;

    for (int i = start_y; i <= stop_y; ++i) {
        for (int j = start_x; j <= stop_x; ++j) {
            if (worldMatrix[i][j] == TILE_BRICK) {
                SDL_Rect brickBox = { j * 64, i * 64, 64, 64 };
                if (SDL_HasIntersection(&playerBox, &brickBox)) {
                    if (proposedY > currentY) {
                        // Moving down; place the player above the brick
                        return brickBox.y - playerBox.h;
                    } else {
                        // Moving up; place the player below the brick
                        return brickBox.y + brickBox.h;
                    }
                }
            }
        }
    }
    return proposedY; // No collision
}
