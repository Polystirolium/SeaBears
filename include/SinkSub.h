#ifndef SINKSUB_H
#define SINKSUB_H

#include "raylib.h"
#include "raymath.h"
#include "Engine.h"
#include "Destroyer.h"
#include "Submarine.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Sky.h"
#include "Ground.h"
#include "GameWindow.h"
#include <algorithm>
#include <vector>

class SinkSub
{

public:
    SinkSub(int winWidth, int winHeight);
    void Tick(float deltaTime);
    STATUS GetGameStatus();
    ~SinkSub();

private:
    void SubInit();
    void DropBombs(POSITION pos);
    void ResetLevel();
    void SetLvlMsgPos();
    void DrawBacking(float posX, float posY, float width, float height);
    void DrawBombIcon(float posX, float posY);

    void DrawUI(int frame);

    int winWidth_;
    int winHeight_;

    // Переменные кадра
    const int maxFrame_ = 60;
    float runningTime_ = 0.f;
    float updateTime_ = 1 / static_cast<float>(maxFrame_);
    int frame_ = 0;

    // Корабль
    Texture2D shipTex_;
    Texture2D shipTexExpl_;
    Destroyer *ship_ = nullptr;

    // Подлодки
    Texture2D subTex_;
    Texture2D subTexExpl_;
    std::vector<Submarine> subList_;
    unsigned char minSubs_{4};
    unsigned char maxSubs_{12};

    // Глубинные бомбы
    Texture2D bombTex_;
    std::vector<Bomb> bombList_;

    // Мины
    Texture2D mineTex_;
    std::vector<Mine> mineList_;

    // Взрывы
    Texture2D explTex_;
    Texture2D splashTex_;
    std::vector<Explosion> explList_;

    // Море
    int seaBeginY_;
    int seaEndY_;

    // Грунт
    Ground *seabed_;

    // Небо
    Texture2D seagullTex_;
    Texture2D cloudTex_;
    Sky *sky_ = nullptr;

    // Интерфейс
    Texture2D iconTex_;
    Texture2D GameOverTex_;
    int fontSize_{75};
    int imgCenter = GameOverTex_.width / 2;
    int gmOverCenter = MeasureText("GAME OVER", fontSize_) / 2;

    // Идентификатор бомбы
    int bmbId{0};

    // Шрифт
    Font levelFont_;
    Font bldFont_;

    bool isLevelMsg{true};
    bool isFading{false};
    bool isGameOver{false};
    bool isPause{false};
    unsigned char msgAlpha_{0};
    Vector2 lvlMsgPos_{0, 0};
    char bombCnt_{4};
    char shipLifes_{0};
    char score_{0};

    int level_{1};

    // Окна
    GameWindow *gameOverWindow_ = nullptr;
    GameWindow *pauseWindow_ = nullptr;
    STATUS gameStatus_ = STATUS::IDLE;
};

#endif