#include "user_interface.h"

// Global variables for font and renderer
static TTF_Font *font = NULL;
static SDL_Renderer *renderer = NULL;

void initiate_user_interface() {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        // Handle error
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    // Load a font
    font = TTF_OpenFont("./assets/fonts/Silkscreen-Regular.ttf", 24); // Specify your font path and size
    if (font == NULL) {
        // Handle error
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
}

void print_user_interface_with_outline(SDL_Renderer* renderer, const char* string, int x, int y) {    
    if (!renderer || !font) {
        // Handle error
        printf("UI not initialized or font not loaded.\n");
        return;
    }

    SDL_Color outlineColor = {80, 80, 80}; // Dark gray outline
    int outlineSize = 2; // Smaller outline size for testing

    // Set the font outline
    TTF_SetFontOutline(font, outlineSize);

    // Create surface for the outline
    SDL_Surface *outlineSurface = TTF_RenderText_Solid(font, string, outlineColor);
    if (!outlineSurface) {
        // Handle error
        printf("Unable to render outline text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture for the outline
    SDL_Texture *outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
    if (!outlineTexture) {
        // Handle error
        printf("Unable to create outline texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(outlineSurface);
        return;
    }

    // Render the outline
    SDL_Rect outlineRect = {x - outlineSize/2, y - outlineSize/2, outlineSurface->w, outlineSurface->h};
    SDL_RenderCopy(renderer, outlineTexture, NULL, &outlineRect);
    SDL_DestroyTexture(outlineTexture);
    SDL_FreeSurface(outlineSurface); // Ensure the surface is freed

    // Set the font outline back to 0 for main text
    TTF_SetFontOutline(font, 0);

    print_user_interface(renderer, string, x, y);
}

void print_user_interface(SDL_Renderer* renderer, const char* string, int x, int y) {
    if (!renderer || !font) {
        // Handle error
        printf("UI not initialized or font not loaded.\n");
        return;
    }

    // Set text color
    SDL_Color textColor = {255, 255, 255}; // White color

    // Create surface from string
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, string, textColor);
    if (!textSurface) {
        // Handle error
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture from surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        // Handle error
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Render texture to screen
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

    // Clean up
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void cleanup_user_interface() {
    // Clean up font and SDL_ttf
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}
