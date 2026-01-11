#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "raymath.h"

class UI
{

public:
    UI(Texture2D *icons, int winWidth, int winHeight);
    void UIreset();
    void UIreset(int level);
    void UIreset(unsigned char shipLifes, int score);
    void Tick(int frame);
    void SetSubCnt(unsigned char cnt);
    void SetLevel(int level);
    bool GetisReadyToAttack();
    void IncreaseBombs();
    void DecreaseBombs();
    void DecreaseLifes();
    void AddScore();

    ~UI();

private:
    void DrawBacking(float posX, float posY, float width, float height);
    void DrawBombIcon(float posX, float posY);
    void SetLvlTxtPos();

    Texture2D *icons_;
    Font levelFont_;
    Font bldFont_;

    int winWidth_;
    int winHeight_;
    int fntSize{75};
    int level_;

    unsigned char shipLifes_{2};
    unsigned char subCnt_{2};
    unsigned char bombCnt_{4};
    unsigned char txtAlpha{255};
    int score_{0000000};

    float posX{70};
    float posY{52};

    Vector2 lvlPos_{};
    Vector2 scrPos_{};

    bool isLevelTXTshowing{true};
    bool isFirstGroup{true};
};

#endif