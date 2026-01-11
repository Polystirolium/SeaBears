#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "raymath.h"

class Sprite
{

public:
    Sprite() = delete;
    // Текстура, позиция X, позиция Y, ширина текстуры, высота текстуры
    Sprite(Texture2D *texture, float posX, float posY, float texWidth, float texHeight, int id);
    // Текстура, позиция X, позиция Y, ширина текстуры, высота текстуры, делитель числа кадров
    Sprite(Texture2D *texture, float posX, float posY, float texWidth, float texHeight, int fps, int frameDivider);
    void Tick();
    void Tick(int frame, bool &isPause);
    void Die();
    void SetLeftRight(float leftRight);
    Vector2 GetVelocity();
    Vector2 GetPosition();
    float GetTexWidth();
    float GetLeftRight();
    void SetVelocity(Vector2 velocity);
    void SetVelocityBySide();
    bool GetIsAlive();
    ~Sprite();

private:
    Texture2D *texture_ = nullptr;
    Vector2 position_;
    float texWidth_{0};
    float texHeight_{0};
    float scale_{0.4f};
    float leftRight_{1.f};
    int frameDivider_{0};
    bool animated_{false};
    bool repeatable{true};

    int horizontalFrame_{0};
    int verticalFrame_{0};
    int curFrame_{0};
    int maxFrames_{0};

    Vector2 velocity_{-0.3f, 0.1f};

    int id_{0};
    int fps{0};

    bool isAlive{true};
};

#endif