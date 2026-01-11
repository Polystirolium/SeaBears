#include "UI.h"

UI::UI(Texture2D *icons, int winWidth, int winHeight) : icons_(icons), winWidth_(winWidth), winHeight_(winHeight)
{
    // Загрузка шрифта с поддержкой кириллицы и латиницы
    // levelFont_ = LoadFont("Fonts/arial.ttf");
    levelFont_ = LoadFontEx("Fonts/arial.ttf", fntSize, NULL, 0);
    bldFont_ = LoadFontEx("Fonts/arialbd.ttf", 25, NULL, 0);
    SetLvlTxtPos();
}

void UI::UIreset()
{
    txtAlpha = 255;
    isLevelTXTshowing = true;
    SetLvlTxtPos();
    bombCnt_ = 4;
}

void UI::UIreset(int level)
{
    level_ = level;
    txtAlpha = 255;
    isLevelTXTshowing = true;
}

void UI::UIreset(unsigned char shipLifes, int score)
{
    txtAlpha = 255;
    isLevelTXTshowing = true;
    SetLvlTxtPos();
    bombCnt_ = 4;
    score_ = score;
    shipLifes_ = shipLifes;
}

void UI::Tick(int frame)
{
    //{53.f, 42.f, 140.f, 65.f};
    DrawBacking(50.f, 42.f, 140.f, 65.f);
    DrawTextEx(bldFont_, TextFormat("Level %i", level_), {50.f, 120.f}, 25, 0, {161, 134, 96, 255});
    DrawBacking(1040.f, 42.f, 190.f, 65.f);

    DrawTextEx(bldFont_, TextFormat("X %i", shipLifes_), {135.f, 50.f}, 25, 0, {235, 235, 235, 255});
    DrawTextEx(bldFont_, TextFormat("X %i", subCnt_), {135.f, 75.f}, 25, 0, {235, 235, 235, 255});
    DrawTextEx(bldFont_, TextFormat("Score %i", score_), {1055.f, 50.f}, 25, 0, {235, 235, 235, 255});

    float scrPosX = 1055.f;
    for (size_t i = 0; i < bombCnt_; i++)
    {
        DrawBombIcon(scrPosX, 85.f);
        scrPosX = scrPosX + 15;
    }

    Rectangle sourceText{0.f, 0.f, 49.f, 40.f};
    Rectangle destText{posX, posY, 49.f, 40.f};
    DrawTexturePro(*icons_, sourceText, destText, {0.0, 0.0}, 0.f, WHITE);

    if (isLevelTXTshowing)
    {
        DrawTextEx(levelFont_, TextFormat("Level %i", level_), lvlPos_, fntSize, 10, {128, 78, 56, txtAlpha});

        if (txtAlpha > 10)
        {
            if (frame % 2 == 0)
            {
                txtAlpha = txtAlpha - 10;
            }
        }
        else
        {
            isLevelTXTshowing = false;
        }
    }
}

void UI::SetSubCnt(unsigned char cnt)
{
    subCnt_ = cnt;
}

void UI::SetLevel(int level)
{
    level_ = level;
}

UI::~UI()
{
    UnloadFont(levelFont_);
    UnloadFont(bldFont_);
}

void UI::SetLvlTxtPos()
{
    int txtWidth = MeasureText(TextFormat("Level %i", level_), fntSize);
    lvlPos_ = {static_cast<float>(winWidth_ / 2 - txtWidth / 2),
               static_cast<float>(winHeight_ / 2 - fntSize / 2)};
}

void UI::DrawBacking(float posX, float posY, float width, float height)
{
    DrawRectangleRounded({posX, posY, width, height}, 0.20f, 0, {209, 193, 130, 255});
    DrawRectangleRoundedLines({posX, posY, width, height}, 0.25f, 0, 2.f, {121, 79, 57, 255});
}

void UI::DrawBombIcon(float posX, float posY)
{
    DrawRectangle(posX, posY, 6.f, 10.f, {121, 79, 57, 255});
    DrawLine(posX - 1, posY + 3, posX + 7, posY + 3, {121, 79, 57, 255});
    DrawLine(posX - 1, posY + 7, posX + 7, posY + 7, {121, 79, 57, 255});
}

bool UI::GetisReadyToAttack()
{
    return bombCnt_ > 0;
}

void UI::IncreaseBombs()
{
    bombCnt_++;
}

void UI::DecreaseBombs()
{
    if (bombCnt_ > 0)
    {
        bombCnt_--;
    }
    else
    {
        isFirstGroup = false;
    }
}

void UI::DecreaseLifes()
{
    if (shipLifes_ > 0)
    {
        shipLifes_--;
    }
}

void UI::AddScore()
{
    if (isFirstGroup && bombCnt_ == 3)
    {
        score_ = score_ + 100;
    }
    else
    {
        score_ = score_ + 10;
    }
}
