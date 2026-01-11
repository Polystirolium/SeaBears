#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "raylib.h"
#include "raymath.h"
#include "Engine_Math.h"
#include <algorithm>
#include <ctime>
#include <random>
#include "Destroyer.h"
#include "Mine.h"
#include <vector>

class Submarine
{
public:
    // текстура, позиция по X, по Y, масштаб, скорость, положение
    Submarine(Texture2D *texture, Texture2D *textureExpl, Texture2D *textureMine,
              Destroyer *destroyer, int seaTop, float posX, float posY, float scale, float speed, float rightLeft);
    void Ai(std::vector<Mine> &mines, bool &isPause);
    void SetBorders_X(float left, float right);
    float GetSubWidth();
    float GetSubHeight();
    bool CheckCollision(Rectangle rect);
    void DrawHitBox();
    void Die();
    bool GetIsAlive();
    void Tick(int frame, bool &isPause);
    ~Submarine();

private:
    Texture2D *texture_;
    Texture2D *textureExpl_;
    Texture2D *textureMine_;
    Destroyer *destroyer_ = nullptr;

    int seaTop_{0};

    Vector2 subPos_{};
    float scale_{};
    Vector2 defaultVel_{1.f, 0.f};
    float rightLeft_ = 1.f;
    Vector2 velocity_{1.f, 0.f};

    Vector2 orign_{0.f, 0.f};
    int subFrame = 0;
    int explFrame = 0;
    int startFrame = 0;
    int endFrame = 5;

    int reChargeTime = 0;
    int reChargeMax = 5;

    float subWidth = 172.f;
    float subHeight = 38.f;
    int previosFrame{60};
    Color color{255, 255, 255, 255};

    // Границы столкновения
    std::vector<Point> hitPolygon_{{0.f, 23.f}, {64.f, 23.f}, {64.f, 14.f}, {92.f, 14.f}, {92.f, 22.f}, {172.f, 22.f}, {159.f, 36.f}, {46.f, 36.f}, {46.f, 30.f}, {11.f, 30.f}, {0.f, 30.f}};

    // Границы моря
    float maxPosX{0.f};
    float minPosX{0.f};
    float curLaunchX{0.f};

    bool isOutOfScreen{true};
    bool isAlive{true};
    bool isDiying{false};
    bool isDoRotation{false};
    bool isReadyAttack{false};

    // Проверка точки в полигоне
    bool isPointInPolygon(const Point &point);
    // Отзеркаливание подлодки
    void FlipCollisionBox();
};

#endif