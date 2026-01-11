#include "Bomb.h"

Bomb::Bomb(Texture2D *texture, float posX, float posY, float scale, int id) : texture_(texture), scale_(scale), id_(id)
{
    bombPos_ = {posX, posY - bombHeight / 2};

    orign_ = {0.f, 0.f};

    // Collider
    hitBox_ = {bombPos_.x, bombPos_.y + bombHeight * .7f * scale_,
               bombWidth * scale_, bombHeight * .3f * scale_};
}

Vector2 Bomb::GetVelocity()
{
    return velocity_;
}

Vector2 Bomb::GetPosition()
{
    return Vector2(bombPos_);
}

float Bomb::GetBombWidth()
{
    return bombWidth;
}

float Bomb::GetBombHeight()
{
    return bombHeight;
}

Rectangle Bomb::GetHitbox()
{
    return hitBox_;
}

bool Bomb::GetIsAlive()
{
    return isAlive;
}

void Bomb::Die()
{
    isAlive = false;
}

void Bomb::Tick(int frame, bool &isPause)
{
    if (!isPause)
    {

        if (frame % 10 == 0)
        {
            bombFrame++;

            if (bombFrame == endFrame ||
                bombFrame > endFrame)
            {

                bombFrame = startFrame;
            }
        }

        if ((frame % 40 == 0) && (velocity_.y > 0.3f))
        {
            velocity_.y = velocity_.y - 0.05f;
        }

        if (frame != previousFrame)
        {
            bombPos_ = Vector2Add(bombPos_, velocity_);
            previousFrame = frame;
        }
    }
    Rectangle sourceText{bombFrame * bombWidth, 0.f, bombWidth, bombHeight};
    Rectangle destText{bombPos_.x, bombPos_.y, bombWidth * scale_,
                       bombHeight * scale_};

    DrawTexturePro(*texture_, sourceText, destText, orign_, 0.f, WHITE);

    hitBox_.x = bombPos_.x;
    hitBox_.y = bombPos_.y + bombHeight * .7f * scale_;
    // DrawRectangleLines(hitBox_.x, hitBox_.y, hitBox_.width, hitBox_.height, RED);
}

Bomb::~Bomb()
{
}
