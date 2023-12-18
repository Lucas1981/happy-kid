#include "graphics.h"
#include <math.h>

static SDL_Renderer* renderer = NULL;
static SDL_Window* window = NULL;

SDL_Renderer* get_renderer() {
    return renderer;
}

int init_graphics() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Happy Kid",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Without the SDL_RENDERER_PRESENTVSYNC flag set, the frame rate gets choppy and the performance is bad.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return 1;
}

void cleanup_graphics() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
