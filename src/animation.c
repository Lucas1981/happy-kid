#include "animation.h"
#include "image_loader.h"  // For the load_image function

void init_animation(Animation* animation, SDL_Renderer* renderer, const char** frameFiles, int numFrames, Uint32 frameDuration) {
    animation->frames = malloc(numFrames * sizeof(SDL_Texture*));
    animation->numFrames = numFrames;
    animation->currentFrame = 0;
    animation->frameDuration = frameDuration;
    animation->lastFrameChange = 0;

    for (int i = 0; i < numFrames; ++i) {
        animation->frames[i] = load_image(frameFiles[i], renderer);
    }
}

void update_animation(Animation* animation, Uint32 deltaTime) {
    animation->lastFrameChange += deltaTime;
    if (animation->lastFrameChange >= animation->frameDuration) {
        animation->currentFrame = (animation->currentFrame + 1) % animation->numFrames;
        animation->lastFrameChange = 0;
    }
}

void render_animation(SDL_Renderer* renderer, Animation* animation, SDL_Rect* destRect) {
    SDL_RenderCopy(renderer, animation->frames[animation->currentFrame], NULL, destRect);
}
