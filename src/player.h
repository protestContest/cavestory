#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/scoped_ptr.hpp>
#include "sprite.h"

struct Sprite;
struct Graphics;

class Player {
public:
    Player(Graphics& graphics, int x, int y);

    void update(int elapsed_time_ms);
    void draw(Graphics& graphics);
    
    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

private:
    int x_, y_;
    boost::scoped_ptr<Sprite> sprite_;
    float velocity_x_;
    float acceleration_x_;
};

#endif
