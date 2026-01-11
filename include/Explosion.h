#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "raylib.h"
#include "raymath.h"

class Explosion
{
public:
    Explosion() = delete;
    Explosion(Texture2D *texture, float posX, float posY, float width, float height, float scale);
    void Tick(int frame, bool &isPause);
    bool GetIsAlive();
    ~Explosion();

private:
    Texture2D *texture_;
    Vector2 explposionPos_{};
    Vector2 orign_{0.f, 0.f};
    int explFrame = 0;
    int endFrame = 9;

    float explWidth_ = 38.f;
    float explHeight_ = 38.f;

    int horizontalFrame_{0};
    int verticalFrame_{0};

    int curHorizontalFrame_;
    int curVerticalFrame_;

    float scale_{};
    bool isAlive{true};
};

#endif