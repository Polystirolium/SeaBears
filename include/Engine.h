#ifndef ENGINE_H
#define ENGINE_H

#include "raylib.h"
#include "raymath.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "Mine.h"
#include <vector>
#include "Engine_Math.h"
#include "Bomb.h"

enum class STATUS
{
    IDLE,
    RESETLEVEL,
    EXIT
};

bool CheckCollision(Rectangle rectOne, Rectangle rectTwo);
bool CheckCollision(Destroyer *destroyer, Mine *mine);

void SubInit(std::vector<Submarine> *list, Texture2D *subTexture, Texture2D *subExplTexture,
             Texture2D *mineTexture, Destroyer *destroyer, Rectangle sea, int level);

void ResetLevel(std::vector<Submarine> *list, Texture2D *texture, Texture2D *textureExpl, Texture2D *mineTexture,
                Destroyer *destroyer, Rectangle sea, int level);

void Framer(int frame, int devider, int &animFrame);

void Timer(int fps, int frame, int &seconds);

#endif