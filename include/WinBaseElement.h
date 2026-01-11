#ifndef WINBASEELEMENT_H
#define WINBASEELEMENT_H

#include "raylib.h"
#include "raymath.h"

class WinBaseElement
{

public:
    WinBaseElement() = delete;
    WinBaseElement(float posX, float posY, float width, float height, int id);
    int GetID();
    bool GetIsClicked();
    virtual void Tick(int frame, Vector2 mousePos);
    void ResetElement();
    ~WinBaseElement();

private:
protected:
    bool isMouseOver(Vector2 mousePos);
    bool isClicked{false};
    unsigned char alpha_{0};
    unsigned char maxAlpha_{255};
    float posX_;
    float posY_;
    float startPosX_;
    float startPosY_;
    float endPosX_;
    float endPosY_;
    float width_;
    float height_;
    int id_;
    int timeCnt_;
    int startTime_;
};

#endif