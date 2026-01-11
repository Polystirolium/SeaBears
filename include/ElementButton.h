#ifndef ELEMENTBUTTON_H
#define ELEMENTBUTTON_H

#include "WinBaseElement.h"

class ElementButton : public WinBaseElement
{

public:
    ElementButton() = delete;
    ElementButton(const char *txt, float posX, float posY, float width,
                  float height, Font *font, int fontSize, int id);
    virtual void Tick(int frame, Vector2 mousePos) override;
    ~ElementButton();

private:
    const char *txt_;
    Font *font_;
    int fontSize_;
    float txtPosX_;
    float txtPosY_;
};

#endif