#include "ElementText.h"

ElementText::ElementText(const char *txt, float posX, float posY, Font *font, int fontSize, int id) : WinBaseElement(posX, posY, 0, 0, id),
                                                                                                      txt_(txt), font_(font), fontSize_(fontSize)
{
    // Задаём параметры для анимации наплыва
    endPosX_ = posX_;
    endPosY_ = posY_;
    startPosX_ = posX_;
    startPosY_ = posY_ - 25.5f;

    posY_ = startPosY_;

    timeCnt_ = 0;
    startTime_ = 30;
}

void ElementText::Tick(int frame, Vector2 mousePos)
{
    DrawTextEx(*font_, txt_, {posX_, posY_}, fontSize_, 0.f, {121, 79, 57, alpha_});
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

ElementText::~ElementText()
{
}
