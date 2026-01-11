#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <memory>

#include "WinBaseElement.h"
#include "ElementButton.h"
#include "ElementText.h"
#include "ElementImage.h"
#include "Engine.h"

class GameWindow
{

public:
    GameWindow(float posX, float posY, float width, float height);
    void Tick(Vector2 mousePos, int frame, STATUS &winStatus);
    void AddElement(std::unique_ptr<WinBaseElement> element);
    void ResetWindow();
    STATUS GetWinStatus();
    float GetWidth();
    float GetHeight();
    float GetPosX();
    ~GameWindow();

private:
    float posX_;
    float posY_;
    float width_;
    float height_;

    bool fadeIn{true};
    unsigned char alpha_{0};
    unsigned char maxAlpha_{190};

    std::vector<std::unique_ptr<WinBaseElement>>
        elements;
    STATUS winStatus_ = STATUS::IDLE;
};

#endif