#include "Player.h"

#include <iostream>

Player::Player(SDL_Renderer* renderer)
    : run(), playAgain() ,frame(0), elapsed(0), playerX(200), playerY(372), playerWidth(48), playerHeight(60), velocityY(0), gravity(1), playing(true), score(0)

{
    const char* runPath[2] = {"player_walk_1.png", "player_walk_2.png"};

    const char* playAgainPath = "playagain.png";
    
    for (int i=0; i<2; i++){
        run[i] = IMG_LoadTexture(renderer, runPath[i]);
    }

    playAgain = IMG_LoadTexture(renderer, playAgainPath);

}

void Player::draw(SDL_Renderer* renderer, Enemies& enemies){
    if (playing){
        SDL_Rect playerRect = {playerX, playerY, playerWidth, playerHeight};

        SDL_RenderCopy(renderer, run[frame], NULL, &playerRect);

        enemies.draw(renderer);
    } else {
        SDL_Rect playAgainRect = {100, 200, 600, 200};

        SDL_RenderCopy(renderer, playAgain, NULL, &playAgainRect);
    }
}

void Player::update(Enemies& enemies){
    if (playing){
        score++;
        
        updateFrames();
        enemyCollision(enemies);
        verticalMovement();
        groundCollision();

        enemies.update();
    }
}

void Player::updateFrames(){
    elapsed++;
    if (elapsed % 10 == 0){
        frame = (frame + 1) % 2;
    }
}

void Player::setJump(){
    if (playing){
        if (velocityY == 0){
            velocityY = -20;
        }
    }
}

void Player::verticalMovement(){
    velocityY += gravity;
    playerY += velocityY;
}

void Player::groundCollision(){
    if (playerY + playerHeight >= 432){
        velocityY = 0;
        playerY = 432 - playerHeight - 1;
    }
}

void Player::enemyCollision(Enemies enemies){
    if (
        playerX <= enemies.getSnailX() + enemies.getSnailWidth() &&
        playerX + playerWidth >= enemies.getSnailX() &&
        playerY + playerHeight >= enemies.getSnailY() &&
        playerY <= enemies.getSnailY() + enemies.getSnailHeight()
    ){
        playing = false;
    }

    if (
        playerX <= enemies.getFlyX() + enemies.getFlyWidth() &&
        playerX + playerWidth >= enemies.getFlyX() &&
        playerY + playerHeight >= enemies.getFlyY() &&
        playerY <= enemies.getFlyY() + enemies.getFlyHeight()
    ){
        playing = false;    
    }
}


void Player::restartGame(Enemies enemies){
    playerY = 372;
    enemies.resetPosition();
    playing = true;
}

bool Player::getPlaying(){
    return playing;
}