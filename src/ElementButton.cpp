#include "ElementButton.h"

ElementButton::ElementButton(const char *txt, float posX, float posY, float width,
                             float height, Font *font, int fontSize, int id) : WinBaseElement(posX, posY, width, height, id),
                                                                               txt_(txt), font_(font), fontSize_(fontSize),
                                                                               txtPosX_(width / 2 - MeasureTextEx(*font, txt, fontSize, 0.f).x / 2),
                                                                               txtPosY_(height / 2 - MeasureTextEx(*font, txt, fontSize, 0.f).y / 2)
{
    endPosX_ = posX_;
    endPosY_ = posY_;
    startPosX_ = posX_;
    startPosY_ = posY_ - 25.5f;
    posY_ = startPosY_;

    timeCnt_ = 0;
    startTime_ = 40;
}

void ElementButton::Tick(int frame, Vector2 mousePos)
{
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

    if (isMouseOver(mousePos))
    {
        DrawRectangleRounded({posX_, posY_, width_, height_}, 0.1f, 0, {121, 79, 57, alpha_});
        DrawTextEx(*font_, txt_, {posX_ + txtPosX_, posY_ + txtPosY_}, fontSize_, 0.f, {240, 235, 222, alpha_});
        if (IsMouseButtonPressed(0))
        {
            isClicked = true;
        }
    }
    else
    {
        DrawRectangleRoundedLines({posX_, posY_, width_, height_}, 0.10f, 0, 2.f, {121, 79, 57, alpha_});
        DrawTextEx(*font_, txt_, {posX_ + txtPosX_, posY_ + txtPosY_}, fontSize_, 0.f, {121, 79, 57, alpha_});
    }
}

ElementButton::~ElementButton()
{
}
