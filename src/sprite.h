#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL/SDL.h>

struct Graphics;

class Sprite {
public:
    Sprite(const std::string& file_path,
            int source_x, int source_y,
            int width, int height);
    virtual ~Sprite();
    virtual void update(int) {}

    void draw(Graphics& graphics, int x, int y);

protected:
    SDL_Rect source_rect_;

private:
    SDL_Surface* sprite_sheet_;
};

#endif
