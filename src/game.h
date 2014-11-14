#ifndef GAME_H_
#define GAME_H_

struct SDL_Surface;

class Game {
public:
    Game();
    ~Game();
private:
    void eventLoop();
    void update();
    void draw();

    SDL_Surface* screen_;
};

#endif
