#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "sprite.h"

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite(
            Graphics& graphics,
            const std::string& file_path,
            int source_x, int source_y,
            int width, int height,
            int fps, int num_frames);
  
    void update(int);

private:
    const int frame_time_;
    const int num_frames_;
    int current_frame_;
    int elapsed_time_;
};

#endif
