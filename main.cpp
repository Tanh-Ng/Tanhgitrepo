#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "BackGround.h"
#include "Player.h"
#include "Enemies.h"


int isRunning = true;
int mTicksCount = 0;

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)){}

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f){
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();
}

void input(Player& player, Enemies enemies){
    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    // Handle keydown event
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            player.setJump();
                        
                        if (player.getPlaying()){
                            case SDLK_p:
                                player.restartGame(enemies);
                        }
                    }
                    break;
            }
        }
}

void output(SDL_Renderer* renderer, BackGround& backGround, Player& player, Enemies& enemies){
    SDL_RenderClear(renderer);

    backGround.draw(renderer);
    player.update(enemies);
    player.draw(renderer, enemies);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "Failed to initialize SDL_Image: " << SDL_GetError() << std::endl;
    }


    SDL_Window* window = SDL_CreateWindow(
        "Endless Runner",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (!window){
        std::cout << "Failed to create Window: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer){
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    }

    BackGround BackGround(renderer);
    Player player(renderer);
    Enemies enemies(renderer);

    while (isRunning){
        input(player, enemies);
        update();
        output(renderer, BackGround, player, enemies);
    }

    return 0;
}
