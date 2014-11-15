#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct SDL_Surface;
struct SDL_Rect;

class Graphics {
public:
    Graphics();
    ~Graphics();

    void blitSurface(
            SDL_Surface* source,
            SDL_Rect* source_rectangle,
            SDL_Rect* destination_rectangle);

    void flip();
    void clear();

private:
    SDL_Surface* screen_;
};

#endif
