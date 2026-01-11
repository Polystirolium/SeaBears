#include "WinBaseElement.h"

WinBaseElement::WinBaseElement(float posX, float posY, float width, float height, int id) : posX_(posX), posY_(posY),
                                                                                            width_(width), height_(height), id_(id)
{
}

void WinBaseElement::Tick(int frame, Vector2 mousePos)
{
}

void WinBaseElement::ResetElement()
{
    posX_ = startPosX_;
    posY_ = startPosY_;
    isClicked = false;
    timeCnt_ = 0;
    alpha_ = 0;
}

WinBaseElement::~WinBaseElement()
{
}

bool WinBaseElement::isMouseOver(Vector2 mousePos)
{

    return ((mousePos.x > posX_ && mousePos.x < posX_ + width_) &&
            (mousePos.y > posY_ && mousePos.y < posY_ + height_));
}

int WinBaseElement::GetID()
{
    return id_;
}

bool WinBaseElement::GetIsClicked()
{
    return isClicked;
}
