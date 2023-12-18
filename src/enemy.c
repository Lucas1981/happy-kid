#include "enemy.h"
#include "animation.h"
#include "collision.h"
#include "world.h"
#include <stdlib.h>
#include "graphics.h"
#include "math.h"

static Enemy* enemies = NULL;
static int numEnemies = 0;
static float moveSpeed = 250.0f; // Pixels per second
static SDL_Renderer* renderer = NULL;

static void load_enemies_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening enemy file");
        return;
    }

    fscanf(file, "%d", &numEnemies); // Read the number of enemies

    if (enemies == NULL) {
        enemies = malloc(numEnemies * sizeof(Enemy));
    }

    for (int i = 0; i < numEnemies; i++) {
        int x, y, dirX, dirY;
        fscanf(file, "%d %d %d %d", &x, &y, &dirX, &dirY);
        enemies[i].position = (SDL_Rect){x, y, 64, 64};
        enemies[i].directionX = dirX;
        enemies[i].directionY = dirY;
        enemies[i].isActive = 1;
    }

    fclose(file);
}

void reset_enemies() {
    load_enemies_from_file("./assets/enemy.txt");
}

void init_enemies() {
    renderer = get_renderer();
    reset_enemies();

    const char* enemyFrames[] = {"./assets/images/fire-guy.png", "./assets/images/fire-guy-2.png"};
    for (int i = 0; i < numEnemies; i++) {
        init_animation(&enemies[i].animation, renderer, enemyFrames, 2, 200); // 200ms per frame
    }
}

static void update_enemy_position_and_direction(Enemy* enemy, char worldMatrix[][WORLD_WIDTH], float timeInSeconds) {
    float deltaMoveX = enemy->directionX * moveSpeed * timeInSeconds;
    float deltaMoveY = enemy->directionY * moveSpeed * timeInSeconds;

    int proposedX = enemy->position.x + (int)deltaMoveX;
    int proposedY = enemy->position.y + (int)deltaMoveY;

    // Collision detection and position adjustment
    int correctedX = check_collision_x(proposedX, enemy->position.x, enemy->position.y, 64, 64, worldMatrix);
    int correctedY = check_collision_y(correctedX, proposedY, enemy->position.y, 64, 64, worldMatrix);

    if (correctedX != proposedX) {
        enemy->directionX *= -1; // Reverse X direction on collision
    }
    if (correctedY != proposedY) {
        enemy->directionY *= -1; // Reverse Y direction on collision
    }

    enemy->position.x = (correctedX + 640) % 640;
    enemy->position.y = (correctedY + 480) % 480;
}

void update_enemies(Uint32 deltaTime, char worldMatrix[][WORLD_WIDTH]) {
    float timeInSeconds = (float)deltaTime / 1000.0f;
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i].isActive) {
            update_enemy_position_and_direction(&enemies[i], worldMatrix, timeInSeconds);
            update_animation(&enemies[i].animation, deltaTime);
            // Additional logic for enemy behavior...
        }
    }
}

void render_enemies() {
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i].isActive) {
            render_animation(renderer, &enemies[i].animation, &enemies[i].position);
        }
    }
}

int get_num_enemies() {
    return numEnemies;
}

Enemy* get_enemies() {
    return enemies;
}

void free_enemies() {
    for (int i = 0; i < numEnemies; i++) {
        for (int j = 0; j < enemies[i].animation.numFrames; j++) {
            SDL_DestroyTexture(enemies[i].animation.frames[j]);
        }
        free(enemies[i].animation.frames);
    }
    free(enemies);
}
