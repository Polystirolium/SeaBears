#include "ElementImage.h"

ElementImage::ElementImage(Texture2D *texture, float posX, float posY,
                           float width, float height, int id) : WinBaseElement(posX, posY, width, height, id),
                                                                texture_(texture)
{
    // Задаём параметры для анимации наплыва
    endPosX_ = posX_;
    endPosY_ = posY_;
    startPosX_ = posX_;
    startPosY_ = posY_ - 25.5f;
    posY_ = startPosY_;

    timeCnt_ = 0;
    startTime_ = 20;
}

void ElementImage::Tick(int frame, Vector2 mousePos)
{
    DrawTexture(*texture_, posX_, posY_, {255, 255, 255, alpha_});
    if (frame % 1 == 0)
    {
        if (timeCnt_ < startTime_)
        {
            timeCnt_++;
        }

        if (timeCnt_ >= startTime_ && alpha_ < maxAlpha_)
        {
            alpha_ = alpha_ + 10;

            if (alpha_ >= 245)
            {
                alpha_ = 255;
            }

            posY_ = posY_ + .5f;
        }
    }
}

ElementImage::~ElementImage()
{
}
