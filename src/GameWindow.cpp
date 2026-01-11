#include "GameWindow.h"

GameWindow::GameWindow(float posX, float posY, float width, float height) : posX_(posX), posY_(posY),
                                                                            width_(width), height_(height)
{
}

void GameWindow::Tick(Vector2 mousePos, int frame, STATUS &winStatus)
{
    // DrawRectangleRounded({posX_, posY_, width_, height_}, 0.05f, 0, {220, 210, 160, 255});
    // DrawRectangleRoundedLines({posX_, posY_, width_, height_}, 0.10f, 0, 2.f, {121, 79, 57, 255});
    DrawRectangle(0, 0, 1280, 720, {220, 210, 160, alpha_});

    if (frame % 2 == 0 && alpha_ < maxAlpha_)
    {
        alpha_ = alpha_ + 5;
    }

    if (elements.size() > 0)
    {
        for (const auto &el : elements)
        {
            el->Tick(frame, mousePos);
            if (el->GetIsClicked() && el->GetID() == 0)
            {
                winStatus = STATUS::RESETLEVEL;
            }
            else if (el->GetIsClicked() && el->GetID() == 1)
            {
                winStatus = STATUS::EXIT;
            }
        }
    }
}

void GameWindow::AddElement(std::unique_ptr<WinBaseElement> element)
{
    elements.push_back(std::move(element));
}

void GameWindow::ResetWindow()
{
    fadeIn = true;
    alpha_ = 0;
    winStatus_ = STATUS::IDLE;
    if (elements.size() > 0)
    {
        for (const auto &el : elements)
        {
            el->ResetElement();
        }
    }
}

STATUS GameWindow::GetWinStatus()
{
    return winStatus_;
}

float GameWindow::GetWidth()
{
    return width_;
}

float GameWindow::GetHeight()
{
    return height_;
}

float GameWindow::GetPosX()
{
    return posX_;
}

GameWindow::~GameWindow()
{
}
