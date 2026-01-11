#include "Mine.h"

Mine::Mine(Texture2D *texture, float posX, float posY, float scale, int seaTop) : texture_(texture), scale_(scale)
{
    minePos_ = {posX, posY - mineHeight / 2};
    seaTop_ = static_cast<float>(seaTop);
}

Rectangle Mine::GetHitbox()
{
    return {minePos_.x + 1, minePos_.y + 2, minePos_.x + 11, minePos_.y + 10};
}

void Mine::Tick(bool &isPause)
{
    if (isAlive)
    {
        if (!isPause)
        {
            minePos_ = Vector2Add(minePos_, velocity_);
        }

        DrawTexture(*texture_, minePos_.x, minePos_.y, WHITE);

        // Линия по центру
        // DrawLine(minePos_.x + mineWidth / 2, minePos_.y, minePos_.x + mineWidth / 2, minePos_.y + mineHeight, RED);
        // DrawRectangle(minePos_.x + 1, minePos_.y + 2, 10, 8, RED);
    }
}

Vector2 Mine::GetPosition()
{
    return minePos_;
}

float Mine::GetMineWidth()
{
    return mineWidth;
}

float Mine::GetMineHeight()
{
    return mineHeight;
}

bool Mine::GetIsAlive()
{
    return isAlive;
}

void Mine::Die()
{
    isAlive = false;
}

Mine::~Mine()
{
}