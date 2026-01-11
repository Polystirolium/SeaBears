#ifndef GROUND_H
#define GROUND_H

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Ground
{

public:
    Ground(float groundLevel, float winWidth, float winHeight);
    void Draw();
    Rectangle GetHitBox();
    void ReGenerteLandscape();
    ~Ground();

private:
    // Генерация ландшафта минимальная высота, максимальная высота
    void GenerateLandscape(std::vector<Vector2> &landScape,
                           int hMin, int hMax);
    void DrawLandScape(std::vector<Vector2> &landScape, Color color);
    Rectangle groundForm_;
    Rectangle hitBox_;
    float winWidth_;
    float winHeight_;
    int posX;
    int posY;
    int width;
    int height;

    int hMin_{0};
    int hMax_{20};

    std::vector<Vector2> landScapeBack_;
    std::vector<Vector2> landScapeFront_;
};

#endif