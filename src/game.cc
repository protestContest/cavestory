#include "game.h"
#include "graphics.h"
#include "player.h"
#include <SDL/SDL.h>
#include "input.h"
#include "map.h"

namespace {
    const int kFps = 60;
}

int Game::kTileSize = 32;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);

    eventLoop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    player_.reset(new Player(graphics, 320, 240));
    map_.reset(Map::createTestMap(graphics));

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

        if (input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)) {
            player_->stopMoving();
        } else if (input.isKeyHeld(SDLK_LEFT)) {
            player_->startMovingLeft();
        } else if (input.isKeyHeld(SDLK_RIGHT)) {
            player_->startMovingRight();
        } else {
            player_->stopMoving();
        }

        if (input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)) {
            player_->lookHorizontal();
        } else if (input.isKeyHeld(SDLK_UP)) {
            player_->lookUp();
        } else if (input.isKeyHeld(SDLK_DOWN)) {
            player_->lookDown();
        } else {
            player_->lookHorizontal();
        }

        if (input.wasKeyPressed(SDLK_z)) {
            player_->startJump();
        } else if (input.wasKeyReleased(SDLK_z)) {
            player_->stopJump();
        }
        
        const int current_time_ms = SDL_GetTicks();
        update(current_time_ms - last_update_time);
        last_update_time = current_time_ms;

        draw(graphics);

        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int ms_per_frame = 1000 / kFps;
        if (elapsed_time_ms < ms_per_frame) {
            SDL_Delay(ms_per_frame - elapsed_time_ms);
        }
    }



}

void Game::update(int elapsed_time_ms) {
    player_->update(elapsed_time_ms);
    map_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    player_->draw(graphics);
    map_->draw(graphics);
    graphics.flip();
}
