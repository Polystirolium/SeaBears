#include "Submarine.h"

Submarine::Submarine(Texture2D *texture, Texture2D *textureExpl, Texture2D *textureMine, Destroyer *destroyer, int seaTop,
                     float posX, float posY, float scale, float speed, float rightLeft) : texture_(texture), textureExpl_(textureExpl),
                                                                                          textureMine_(textureMine), destroyer_(destroyer),
                                                                                          seaTop_(seaTop), subPos_({posX, posY}), scale_(scale),
                                                                                          defaultVel_({speed, 0.f}), rightLeft_(rightLeft)

{
    orign_ = {0.f, 0.f};
    velocity_ = {defaultVel_.x * rightLeft_, 0.f};
    if (rightLeft_ < 0)
    {
        FlipCollisionBox();
    }
}

void Submarine::Ai(std::vector<Mine> &mines, bool &isPause)
{
    // DrawText()
    float minX = round(destroyer_->GetShipPos().x);
    float maxX = round(destroyer_->GetShipPos().x + destroyer_->GetShipWidth());
    float curSubLaunchX = round(subPos_.x + curLaunchX);

    if (!isPause)
    {
        if (((curSubLaunchX >= minX) && (curSubLaunchX <= maxX)) && (isReadyAttack && destroyer_->GetIsAlive()))
        {
            mines.emplace_back(textureMine_, curSubLaunchX, subPos_.y + 22, 1.f, seaTop_);
            reChargeTime = 0;
            isReadyAttack = false;

            // color = {255, 0, 0, 255};
        }
    }
}

void Submarine::SetBorders_X(float left, float right)
{
    minPosX = left;
    maxPosX = right;
}
float Submarine::GetSubWidth()
{
    return subWidth;
}
float Submarine::GetSubHeight()
{
    return subHeight;
}

bool Submarine::GetIsAlive()
{
    return isAlive;
}

void Submarine::Die()
{
    isDiying = true;
}

void Submarine::Tick(int frame, bool &isPause)
{
    if (!isDiying)
    {
        // Если не пауза
        if (!isPause)
        {
            if (isDoRotation)
            {
                if (frame % 10 == 0)
                {
                    subFrame++;

                    if (subFrame == 5 || subFrame > 5)
                    {
                        subFrame = 0;
                        rightLeft_ = -rightLeft_;
                        velocity_.x = defaultVel_.x * rightLeft_;
                        isDoRotation = false;
                        FlipCollisionBox();
                    }
                }
            }
        }

        if (subPos_.x < minPosX && !isOutOfScreen)
        {
            velocity_.x = 0.f;
            subPos_ = {minPosX, subPos_.y};
            isDoRotation = true;
        }

        if (subPos_.x > maxPosX && !isOutOfScreen)
        {
            velocity_.x = 0.f;
            subPos_ = {maxPosX, subPos_.y};
            isDoRotation = true;
        }
        if (subPos_.x > minPosX && (subPos_.x) < maxPosX)
        {
            isOutOfScreen = false;
        }

        if (!isPause)
        {
            subPos_ = Vector2Add(subPos_, velocity_);
        }

        subPos_ = {(round(subPos_.x * 100) / 100), (round(subPos_.y * 100) / 100)};
        previosFrame = frame;

        Rectangle sourceText{subFrame * subWidth, 0.f, subWidth * rightLeft_, subHeight};
        Rectangle destText{subPos_.x, subPos_.y, subWidth * scale_,
                           subHeight * scale_};
        DrawTexturePro(*texture_, sourceText, destText, orign_, 0.f, color);

        float lX = 86.f + 36.f * rightLeft_;
        curLaunchX = lX;
        // DrawLine(subPos_.x + curLaunchX, subPos_.y, subPos_.x + curLaunchX, subPos_.y + 22, RED);

        // DrawHitBox();
    }
    else
    {
        if (!isPause)
        {
            if (frame % 5 == 0)
            {
                explFrame++;

                if (explFrame == 7 || explFrame > 7)
                {
                    isAlive = false;
                }
            }
        }
        Rectangle sourceText{170.f * (explFrame % 4), 170.f * (explFrame / 4), 170.f, 170.f};
        DrawTextureRec(*textureExpl_, sourceText, {subPos_.x, (subPos_.y - 170.f / 2) + (38.f / 2)}, WHITE);
    }

    // Перезарядка

    if (!isPause)
    {
        if (frame % 60 == 0)
        {
            reChargeTime++;

            if (reChargeTime >= reChargeMax)
            {
                isReadyAttack = true;
                // color = {255, 255, 255, 255};
                reChargeTime = 0;
            }
        }
    }
}

bool Submarine::isPointInPolygon(const Point &point)
{
    bool isInside = false;
    size_t n = hitPolygon_.size();

    for (size_t i = 0, j = n - 1; i < n; j = i++)
    {
        if ((hitPolygon_[i].y + subPos_.y > point.y) != (hitPolygon_[j].y + subPos_.y > point.y) &&
            (point.x < ((hitPolygon_[j].x + subPos_.x) - (hitPolygon_[i].x + subPos_.x)) * (point.y - hitPolygon_[i].y + subPos_.y) /
                               (hitPolygon_[j].y + subPos_.y - hitPolygon_[i].y + subPos_.y) +
                           (hitPolygon_[i].x + subPos_.x)))
        {
            isInside = !isInside;
        }
    }

    return isInside;
}

void Submarine::FlipCollisionBox()
{
    float middle = 86.f;

    for (size_t i = 0; i < hitPolygon_.size(); i++)
    {
        hitPolygon_[i].x = middle + (middle - hitPolygon_[i].x);
    }
}

bool Submarine::CheckCollision(Rectangle rect)
{
    if (isDiying == true)
    {
        return false;
    }
    return isPointInPolygon({rect.x, rect.y}) || isPointInPolygon({rect.x + rect.width, rect.y}) ||
           isPointInPolygon({rect.x + rect.width, rect.y + rect.height}) || isPointInPolygon({rect.x, rect.y + rect.height});
}

void Submarine::DrawHitBox()
{
    size_t n = hitPolygon_.size();
    Point startPoint;
    Point previousPoint;

    for (size_t i = 0; i < n; i++)
    {
        if (i == 0)
        {
            startPoint = hitPolygon_[0];
            previousPoint = startPoint;
        }
        else
        {
            DrawLine(previousPoint.x + subPos_.x, previousPoint.y + subPos_.y,
                     hitPolygon_[i].x + subPos_.x, hitPolygon_[i].y + subPos_.y, RED);
            previousPoint = {hitPolygon_[i].x, hitPolygon_[i].y};
        }
    }
    DrawLine(previousPoint.x + subPos_.x, previousPoint.y + subPos_.y,
             startPoint.x + subPos_.x, startPoint.y + subPos_.y, RED);
}

Submarine::~Submarine()
{
}
