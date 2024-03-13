#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Enemies{
    public:
        Enemies(SDL_Renderer* renderer);

        void draw(SDL_Renderer* renderer);
        void update();
        void move();
        void changeFrames();
        void resetPosition();
        int getSnailX();
        int getSnailY();
        int getSnailWidth();
        int getSnailHeight();
        int getFlyX();
        int getFlyY();
        int getFlyWidth();
        int getFlyHeight();

    private:
        SDL_Texture* snail[2];
        SDL_Texture* fly[2];

        int snailX, snailY, snailWidth, snailHeight;
        int flyX, flyY, flyWidth, flyHeight;
        int frame;
        int snailVelocity, flyVelocity, speedChanger;


};