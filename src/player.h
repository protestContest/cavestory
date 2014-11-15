#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/shared_ptr.hpp>
#include <map>
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
    void startJump();
    void stopJump();

private:
    enum MotionType {
        STANDING,
        WALKING,
    };
    enum HorizontalFacing {
        LEFT,
        RIGHT,
    };

    struct SpriteState {
        SpriteState(MotionType motion_type=STANDING,
                    HorizontalFacing horizontal_facing=LEFT):
            motion_type(motion_type),
            horizontal_facing(horizontal_facing) {}

        MotionType motion_type;
        HorizontalFacing horizontal_facing;
    };
    friend bool operator<(const SpriteState& a, const SpriteState& b);

    class Jump {
    public:
        Jump() : time_remaining_ms_(0), active_(false) {}

        void update(int elapsed_time_ms);
        void reset();

        void reactivate() { active_ = time_remaining_ms_ > 0; }
        void deactivate() { active_ = false; }
        bool active() const { return active_; }

    private:
        int time_remaining_ms_;
        bool active_;
    };

    SpriteState getSpriteState();
    void initializeSprites(Graphics& graphics);


    bool on_ground() { return on_ground_; }
    int x_, y_;
    std::map< SpriteState, boost::shared_ptr<Sprite> > sprites_;
    float velocity_x_, velocity_y_;
    float acceleration_x_;
    HorizontalFacing horizontal_facing_;
    bool on_ground_;
    Jump jump_;
};

#endif
