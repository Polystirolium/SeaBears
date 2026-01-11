#ifndef SHIPS_H
#define SHIPS_H

#include "raylib.h"
#include "raymath.h"

class Destroyer
{

public:
    Destroyer() = delete;
    Destroyer(Texture2D *texture, Texture2D *textureExpl, float posX, float posY);
    void SetVelocity(float vX, float vY);
    void SetVelocityStep(float step);
    void SetPosition(float posX, float posY);
    void SetDefaultPos(float posX, float posY);
    void SetToDefaultPos();
    void IncreaseVelocity_X();
    void DecreaseVelocity_X();
    void SetBorders_X(float left, float right);
    float GetShipWidth();
    float GetShipHeight();
    Vector2 GetShipPos();
    Vector2 GetShipVel();
    Rectangle GetHitbox();

    void Tick(int frame, bool &isPause);

    bool GetIsAlive();
    void SetAlive();
    void Die();

    ~Destroyer();

private:
    Texture2D *texture_;
    Texture2D *textureExpl_;
    int destroyerFrame = 0;
    int explFrame = 0;
    float shipWidth = 190.f;
    float shipHeight = 50.f;
    float velStep_ = 0.f;
    float MaxVelocity_X = 3.0f;
    float MinVelocity_X = -3.0f;

    float maxPosX;
    float minPosX;

    bool isAlive{true};
    bool isDiying{false};

    Vector2 shipPos{0.f, 0.f};
    Vector2 defaultPos{0.f, 0.f};
    Vector2 shipVelocity{0.f, 0.f};
};

#endif