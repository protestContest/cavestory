#ifndef INPUT_H_
#define INPUT_H_

#include <SDL/SDL.h>
#include <map>

class Input {
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event& event);

    bool wasKeyPressed(SDLKey key);
    bool wasKeyReleased(SDLKey key);
    bool isKeyHeld(SDLKey key);

private:
    std::map<SDLKey, bool> held_keys_;
    std::map<SDLKey, bool> pressed_keys_;
    std::map<SDLKey, bool> released_keys_;
};

#endif
