#include "Enemies.h"
#include <random>

Enemies::Enemies(SDL_Renderer* renderer)
    : snail(), fly(), snailX(0), snailY(404), snailWidth(56), snailHeight(28), flyX(0), flyY(320), flyWidth(56), flyHeight(28), frame(0), snailVelocity(4), flyVelocity(3), speedChanger(0)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> snail_dist(900,1400);
    std::uniform_int_distribution<> fly_dist(1000, 1500);

    snailX = snail_dist(gen);
    flyX = fly_dist(gen);

    const char* flyPath[2] = {"fly0.png", "fly1.png"};
    const char* snailPath[2] = {"snail0.png", "snail1.png"};

    for (int i=0; i<2; i++){
        snail[i] = IMG_LoadTexture(renderer, snailPath[i]);
        fly[i] = IMG_LoadTexture(renderer, flyPath[i]);
    }
}

void Enemies::draw(SDL_Renderer* renderer){
    SDL_Rect snailRect = {snailX, snailY, snailWidth, snailHeight};
    SDL_Rect flyRect = {flyX, flyY, flyWidth, flyHeight};

    SDL_RenderCopy(renderer, snail[frame], NULL, &snailRect);
    SDL_RenderCopy(renderer, fly[frame], NULL, &flyRect);
}

void Enemies::update(){
    changeFrames();
    move();
    resetPosition();
}

void Enemies::changeFrames(){
    frame = (frame + 1) % 2;
}

void Enemies::move(){
    snailX -= snailVelocity;
    flyX -= flyVelocity;

    speedChanger++;
    if (speedChanger % 10000 == 0 && snailVelocity < 30 && flyVelocity < 0){
        snailVelocity ++;
        flyVelocity ++;
    }

    if (snailVelocity >= 30 || flyVelocity >= 30){
        snailVelocity = 30;
        flyVelocity = 30;
    }
}

void Enemies::resetPosition(){
    if (snailX <= -40){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> snail_dist(900,1400);

        snailX = snail_dist(gen);
    }
    if (flyX <= -40){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> fly_dist(1000, 1500);

        flyX = fly_dist(gen);   
    }
}

int Enemies::getSnailX(){
    return snailX;
}

int Enemies::getSnailY(){
    return snailY;
}

int Enemies::getSnailWidth(){
    return snailWidth;
}

int Enemies::getSnailHeight(){
    return snailHeight;
}

int Enemies::getFlyX(){
    return flyX;
}

int Enemies::getFlyY(){
    return flyY;
}

int Enemies::getFlyWidth(){
    return flyWidth;
}

int Enemies::getFlyHeight(){
    return flyHeight;
}