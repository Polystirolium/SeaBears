#include "Destroyer.h"
#include "Engine.h"

Destroyer::Destroyer(Texture2D *texture, Texture2D *textureExpl, float posX, float posY) : texture_(texture), textureExpl_(textureExpl)
{
    shipPos = {posX, posY};
    defaultPos = {posX, posY};
}

void Destroyer::SetVelocity(float vX, float vY)
{
    shipVelocity = {vX, vY};
}

void Destroyer::SetVelocityStep(float step)
{
    velStep_ = step;
}

void Destroyer::SetPosition(float posX, float posY)
{
    shipPos = {posX, posY};
}

void Destroyer::SetDefaultPos(float posX, float posY)
{
    defaultPos = {posX, posY};
}

void Destroyer::SetToDefaultPos()
{
    shipPos = defaultPos;
}

void Destroyer::IncreaseVelocity_X()
{
    if (shipVelocity.x < MaxVelocity_X)
    {
        shipVelocity.x = shipVelocity.x + velStep_;
    }
}

void Destroyer::DecreaseVelocity_X()
{
    if (shipVelocity.x > MinVelocity_X)
    {
        shipVelocity.x = shipVelocity.x - velStep_;
    }
}

void Destroyer::SetBorders_X(float left, float right)
{
    minPosX = left;
    maxPosX = right;
}

float Destroyer::GetShipWidth()
{
    return shipWidth;
}

float Destroyer::GetShipHeight()
{
    return shipHeight;
}

Vector2 Destroyer::GetShipPos()
{
    return shipPos;
}

Vector2 Destroyer::GetShipVel()
{
    return shipVelocity;
}

Rectangle Destroyer::GetHitbox()
{
    return {shipPos.x, shipPos.y + 41,
            shipPos.x + shipWidth, shipPos.y + 41};
}

void Destroyer::Tick(int frame, bool &isPause)
{
    if (isAlive)
    {

        Framer(frame, 20, destroyerFrame);
        if (destroyerFrame == 5 || destroyerFrame > 5)
        {
            destroyerFrame = 0;
        }

        // Определение границ
        if (shipPos.x < minPosX)
        {
            shipVelocity.x = 0.f;
            shipPos = {minPosX, shipPos.y};
        }

        if (shipPos.x > maxPosX)
        {
            shipVelocity.x = 0.f;
            shipPos = {maxPosX, shipPos.y};
        }

        if (!isDiying)
        {
            if (!isPause)
            {
                shipPos = Vector2Add(shipPos, shipVelocity);
            }

            Rectangle sourceText{shipWidth * destroyerFrame, 0.f, shipWidth, shipHeight};
            DrawTextureRec(*texture_, sourceText, shipPos, WHITE);
            // DrawLine(shipPos.x, shipPos.y + 41, shipPos.x + shipWidth, shipPos.y + 41, RED);
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
            Rectangle sourceText{shipWidth * (explFrame % 4), 100.f * (explFrame / 4), shipWidth, 100.f};
            DrawTextureRec(*textureExpl_, sourceText, {shipPos.x, shipPos.y - 59.f}, WHITE);
        }
        if (!isAlive)
        {
            destroyerFrame = 0;
            explFrame = 0;
        }
    }
}

bool Destroyer::GetIsAlive()
{
    return isAlive;
}

void Destroyer::SetAlive()
{
    isDiying = false;
    isAlive = true;
    shipPos = defaultPos;
    shipVelocity = {0.f, 0.f};
}

void Destroyer::Die()
{
    isDiying = true;
}

Destroyer::~Destroyer()
{
}
