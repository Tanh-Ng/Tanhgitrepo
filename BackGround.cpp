#include "BackGround.h"

BackGround::BackGround(SDL_Renderer* renderer)
    :skyTexture(), groundTexture()
{
    const char* skyPath = "sky.png";
    skyTexture = IMG_LoadTexture(renderer, skyPath);

    const char* groundPath = "ground.png";
    groundTexture = IMG_LoadTexture(renderer, groundPath);
}

void BackGround::draw(SDL_Renderer* renderer){
    SDL_Rect skyRect = {0, 0, 800, 632};
    SDL_Rect groundRect = {0, 432, 800, 168};

    SDL_RenderCopy(renderer, skyTexture, NULL, &skyRect);
    SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);
}