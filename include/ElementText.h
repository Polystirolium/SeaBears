#ifndef ELEMENTTEXT_H
#define ELEMENTTEXT_H

#include "WinBaseElement.h"

class ElementText : public WinBaseElement
{

public:
    ElementText() = delete;
    ElementText(const char *txt, float posX, float posY, Font *font, int fontSize, int id);
     virtual void Tick(int frame,Vector2 mousePos) override;
    ~ElementText();

private:
    const char *txt_;
    Font *font_;
    int fontSize_;
    
};

#endif