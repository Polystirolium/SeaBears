#ifndef MINE_H
#define MINE_H

#include "raylib.h"
#include "raymath.h"

class Mine
{

public:
    Mine() = delete;
    Mine(Texture2D *texture, float posX, float posY, float scale, int seaTop);
    Rectangle GetHitbox();
    void Tick(bool &isPause);
    Vector2 GetPosition();
    float GetMineWidth();
    float GetMineHeight();
    bool GetIsAlive();
    void Die();
    ~Mine();

private:
    Texture2D *texture_;
    Vector2 minePos_{};
    Vector2 velocity_{0.f, -1.f};
    Vector2 orign_{0.f, 0.f};
    float mineWidth = 12.f;
    float mineHeight = 12.f;
    float scale_{};
    float seaTop_{};
    Rectangle hitBox_;
    bool isAlive{true};
};

#endif