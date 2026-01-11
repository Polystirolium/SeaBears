#ifndef BOMB_H
#define BOMB_H

#include "raylib.h"
#include "raymath.h"

class Bomb
{

public:
    Bomb() = delete;
    Bomb(Texture2D *texture, float posX, float posY, float scale, int id);
    Vector2 GetVelocity();
    Vector2 GetPosition();
    float GetBombWidth();
    float GetBombHeight();
    Rectangle GetHitbox();

    bool GetIsAlive();
    void Die();

    void Tick(int frame, bool &isPause);
    ~Bomb();

private:
    Texture2D *texture_;
    Vector2 bombPos_{};
    Vector2 velocity_{0.f, 1.f};
    Vector2 orign_{0.f, 0.f};
    int bombFrame = 0;
    int startFrame = 4;
    int endFrame = 11;
    int previousFrame{60};
    float bombWidth = 4.f;
    float bombHeight = 24.f;
    float scale_{};
    int id_;
    Rectangle hitBox_;
    bool isAlive{true};
};

#endif