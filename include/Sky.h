#ifndef SKY_H
#define SKY_H

#include "raylib.h"
#include "raymath.h"
#include "Sprite.h"
#include <ctime>
#include <vector>

// Класс, содержащий параметры облака
class Cloud
{

public:
    // Позиция x и y, скорость по x, масштаб,прозрачность, идентификация текстуры
    Cloud(float posX, float posY, float velocity, float scale, unsigned char opacity, int id);
    int GetID();
    Vector2 GetPosition();
    float GetVelocity();
    float GetScale();
    unsigned char GetOpacity();
    void SetPosition(float posX, float posY);
    void UpdatePosition();
    ~Cloud();

private:
    Vector2 position_{};
    Vector2 velocity_{};
    float scale_;
    unsigned char opacity_;
    int id_{0};
};

// Класс, содержащий облака
class Sky
{

public:
    Sky() = delete;
    Sky(Texture2D *texture, Texture2D *seagullTexture, int texWidth, int texHeight, int skyWidth, int skyHeight);
    void CloudInit(std::vector<Cloud> *cloudList, int minCloudsCnt, int maxCloudsCnt, float velocity, float scale, int opacity);
    void ReInitClouds();
    void DrawClouds(std::vector<Cloud> &cloudList, bool &isPause);
    void AddSeagull();
    void Tick(int frame, bool &isPause);
    ~Sky();

private:
    Texture2D *texture_;
    Texture2D *seagullTexture_;

    float texWidth_;
    float texHeight_;

    int skyWidth_;
    int skyHeight_;

    int horizontalFrame_;
    int verticalFrame_;

    int seconds_{0};
    int eventSeed{0};

    bool isActed{false};

    std::vector<Cloud> cloudLayerOne;
    std::vector<Cloud> cloudLayerTwo;

    std::vector<Sprite> spritesList;
};
#endif