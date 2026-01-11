#include "Engine.h"
#include <algorithm>
#include <ctime>
#include <random>
#include "Submarine.h"

// Проверка столкновений
bool CheckCollision(Rectangle rectOne, Rectangle rectTwo)
{
    return CheckCollisionRecs(rectOne, rectTwo);
}

bool CheckCollision(Destroyer *destroyer, Mine *mine)
{
    return ((destroyer->GetHitbox().x < mine->GetHitbox().x) &&
            (destroyer->GetHitbox().width > mine->GetHitbox().width)) &&
           (destroyer->GetHitbox().y > mine->GetHitbox().y);
}

/*
void SubInit(std::vector<Submarine> *list, Texture2D *subTexture, Texture2D *subExplTexture,
             Texture2D *mineTexture, Destroyer *destroyer, Rectangle sea, int level)
{
    if (list->size() > 0)
    {
        list->clear();
    }

    level = std::clamp(level, 0, 99);

    // Линейная интерполяция для диапазона от 2 до 10
    int subCount = 2 + (level * (10 - 2)) / 99;

    // Создаём набор подлодок
    srand(time(NULL));
    float subWidth = 172.f;
    float subHeight = 38.f / 2;
    float rightLeft = 1.f;

    for (int i = 0; i < subCount; i++)
    {
        // Позиция по x
        int dx = rand() % static_cast<int>(sea.width / subWidth - 1);
        float posX = dx * subWidth;

        // Позиция по y
        int dy = rand() % static_cast<int>((sea.height - sea.y) / subHeight - 1);

        if (dy == 0)
        {
            dy = 1;
        }
        float posY = sea.y + dy * subHeight;

        // Направление движения
        int dRightLeft = rand() % 6;
        if (dRightLeft % 2 == 0)
        {
            rightLeft = -rightLeft;
        }

        // Определяем скорость
        float minSpeed = 0.5f;
        float maxSpeed = 0.5f + (2.0f - 0.5f) * (level / 99.0f);
        std::random_device rd;                                    // Получаем случайное число из устройства
        std::mt19937 gen(rd());                                   // Инициализация генератора
        std::uniform_real_distribution<> dis(minSpeed, maxSpeed); // Определяем распределение
        float speed = dis(gen);

        // Добавляем подлодку
        list->emplace_back(subTexture, subExplTexture, mineTexture, destroyer, sea.y, posX, posY, 1, speed, rightLeft);

        // Назначаем рамки движения ПЛ
        list->back().SetBorders_X(sea.x, sea.width - subWidth);
    }
}
    

void ResetLevel(std::vector<Submarine> *list, Texture2D *texture, Texture2D *textureExpl, Texture2D *mineTexture,
                Destroyer *destroyer, Rectangle sea, int level)
{

    SubInit(list, texture, textureExpl, mineTexture, destroyer, sea, level);
    destroyer->SetAlive();
    destroyer->SetToDefaultPos();
}
*/
void Framer(int frame, int devider, int &animFrame)
{
    if (frame % devider == 0)
    {
        animFrame++;

        if (animFrame == 5 || animFrame > 5)
        {
            animFrame = 0;
        }
    }
}

void Timer(int fps, int frame, int &seconds)
{
    if (frame != 0)
    {
        if (fps % frame == 1)
        {
            seconds++;
        }
    }
}
