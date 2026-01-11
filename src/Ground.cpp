#include "Ground.h"
#include <random>

Ground::Ground(float groundLevel, float winWidth, float winHeight) : groundForm_{0.f, groundLevel, winWidth,
                                                                                 winHeight - groundLevel},
                                                                     winWidth_(winWidth), winHeight_(winHeight)
{
    posX = static_cast<int>(groundForm_.x);
    posY = static_cast<int>(groundForm_.y);
    width = static_cast<int>(groundForm_.width);
    height = static_cast<int>(groundForm_.height);
    hitBox_ = groundForm_;
    GenerateLandscape(landScapeBack_, hMin_, hMax_);
    GenerateLandscape(landScapeFront_, hMin_+10, hMax_+10);
}

void Ground::Draw()
{
    /*
   DrawRectangle(posX, posY, width, height, {38, 25, 18, 255});
   DrawRectangleLines(hitBox_.x, hitBox_.y, hitBox_.width, hitBox_.height, RED);
   */
    DrawLandScape(landScapeBack_, {51, 33, 23, 100});
    DrawLandScape(landScapeFront_, {51, 33, 23, 255});
}

Rectangle Ground::GetHitBox()
{
    return hitBox_;
}

void Ground::ReGenerteLandscape()
{
    GenerateLandscape(landScapeBack_, hMin_, hMax_);
    GenerateLandscape(landScapeFront_, hMin_+10, hMax_+10);
}

void Ground::GenerateLandscape(std::vector<Vector2> &landScape, int hMin, int hMax)
{
    landScape.clear();
    int min = 20;
    int max = 50;

    // Создаем генератор случайных чисел
    std::random_device rd;                         // Получаем случайное значение из аппаратного генератора
    std::mt19937 gen(rd());                        // Инициализируем генератор Mersenne Twister
    std::uniform_int_distribution<> dis(min, max); // Определяем равномерное распределение

    // Генерируем случайное число
    int random_rows = dis(gen);
    int shiftX = groundForm_.width / random_rows;
    float vX = shiftX;
    float vY = 0;

    for (int i = 0; i < random_rows; i++)
    {

        std::random_device rd;  // Получаем случайное значение из аппаратного генератора
        std::mt19937 gen(rd()); // Инициализируем генератор Mersenne Twister
        std::uniform_int_distribution<> dis(hMin, hMax);
        vY = groundForm_.y + dis(gen);
        if (i == random_rows - 1)
        {
            vX = winWidth_;
        }

        landScape.emplace_back(Vector2{vX, vY});
        vX = vX + shiftX;
    }
}

void Ground::DrawLandScape(std::vector<Vector2> &landScape, Color color)
{
    Vector2 prevPoint{0, groundForm_.y};
    for (Vector2 &point : landScape)
    {
        // DrawLine(prevPoint.x, prevPoint.y, point.x, point.y, color);
        DrawTriangle(prevPoint, {prevPoint.x, winHeight_}, point, color);
        DrawTriangle({prevPoint.x, winHeight_}, {point.x, winHeight_}, point, color);
        prevPoint = point;
    }
}

Ground::~Ground()
{
}
