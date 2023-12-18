#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>

// Animation structure
typedef struct {
    SDL_Texture** frames;      // Array of frame textures
    int numFrames;             // Number of frames in the animation
    int currentFrame;          // Current frame index
    Uint32 frameDuration;      // Duration of each frame in milliseconds
    Uint32 lastFrameChange;    // Time since the last frame change
} Animation;

// Initialize an animation
void init_animation(Animation* animation, SDL_Renderer* renderer, const char** frameFiles, int numFrames, Uint32 frameDuration);

// Update an animation
void update_animation(Animation* animation, Uint32 deltaTime);

// Render the current frame of an animation
void render_animation(SDL_Renderer* renderer, Animation* animation, SDL_Rect* destRect);

#endif
