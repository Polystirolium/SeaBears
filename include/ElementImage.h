#ifndef ELEMENTIMAGE_H
#define ELEMENTIMAGE_H

#include "WinBaseElement.h"

class ElementImage : public WinBaseElement
{

public:
    ElementImage() = delete;
    ElementImage(Texture2D *texture, float posX, float posY,
                 float width, float height, int id);
    virtual void Tick(int frame, Vector2 mousePos) override;
    ~ElementImage();

private:
    Texture2D *texture_;

};

#endif