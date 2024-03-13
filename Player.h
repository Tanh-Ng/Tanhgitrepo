#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Enemies.h"

class Player{
    public:
        Player(SDL_Renderer* renderer);

        void draw(SDL_Renderer *renderer, Enemies& enemies);

        void update(Enemies& enemies);
        void updateFrames();
        void verticalMovement();
        void groundCollision();
        void enemyCollision(Enemies enemies);
        void setJump();
        void restartGame(Enemies enemies);

        bool getPlaying();

    
    private:
        SDL_Texture* run[2];
        SDL_Texture* playAgain;

        int playerX, playerY, playerWidth, playerHeight;
        int velocityY, gravity;
        int frame, elapsed;
        int score;
        
        bool playing;
};