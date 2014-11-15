#include "game.h"
#include "graphics.h"
#include "animated_sprite.h"
#include <SDL/SDL.h>
#include "input.h"

namespace {
    const int kFps = 60;
}

int Game::kTileSize = 32;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);

    eventLoop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    sprite_.reset(new AnimatedSprite("content/MyChar.bmp", 
          0, 0, Game::kTileSize, Game::kTileSize,
          15, 3));

    bool running = true;
    int last_update_time = SDL_GetTicks();
    while (running) {
        const int start_time_ms = SDL_GetTicks();
        input.beginNewFrame();

        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    input.keyDownEvent(event);
                    break;

                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;

                default:
                    break;
            }
        }

        if (input.wasKeyPressed(SDLK_ESCAPE)) {
            running = false;
        }
        
        const int current_time_ms = SDL_GetTicks();
        update(current_time_ms - last_update_time);
        last_update_time = current_time_ms;

        draw(graphics);

        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        SDL_Delay(1000/kFps - elapsed_time_ms);
    }



}

void Game::update(int elapsed_time_ms) {
    sprite_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    sprite_->draw(graphics, 320, 240);
    graphics.flip();
}
