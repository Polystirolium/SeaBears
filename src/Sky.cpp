#include "Sky.h"
#include "Engine.h"
#include <algorithm>

Cloud::Cloud(float posX, float posY, float velocity, float scale, unsigned char opacity, int id) : position_({posX, posY}), velocity_({velocity, 0.f}),
                                                                                                   scale_(scale), opacity_(opacity), id_(id)
{
}

int Cloud::GetID()
{
    return id_;
}

Vector2 Cloud::GetPosition()
{
    return position_;
}

float Cloud::GetVelocity()
{
    return velocity_.x;
}

float Cloud::GetScale()
{
    return scale_;
}

unsigned char Cloud::GetOpacity()
{
    return opacity_;
}

void Cloud::SetPosition(float posX, float posY)
{
    position_ = {posX, posY};
}

void Cloud::UpdatePosition()
{
    position_ = Vector2Add(position_, velocity_);
    position_ = {(round(position_.x * 10) / 10), position_.y};
}

Cloud::~Cloud()
{
}

Sky::Sky(Texture2D *texture, Texture2D *seagullTexture, int texWidth, int texHeight, int skyWidth, int skyHeight) : texture_(texture), seagullTexture_(seagullTexture),
                                                                                                                    texWidth_(static_cast<float>(texWidth)),
                                                                                                                    texHeight_(static_cast<float>(texHeight)),
                                                                                                                    skyWidth_(skyWidth), skyHeight_(skyHeight),
                                                                                                                    horizontalFrame_(texture_->width / texWidth_),
                                                                                                                    verticalFrame_(texture_->height / texHeight_)
{
    // Инициализируем облака
    CloudInit(&cloudLayerOne, 5, 15, 0.1f, 0.5f, 125);
    CloudInit(&cloudLayerTwo, 3, 15, 0.2f, 1.f, 255);
}

void Sky::CloudInit(std::vector<Cloud> *cloudList, int minCloudsCnt, int maxCloudsCnt,
                    float velocity, float scale, int opacity)
{

    // Определяем сколько вариантов облаков в текстуре
    int cloudsVersion = (texture_->width / texWidth_) * (texture_->height / texHeight_);

    // Определдяем количество
    srand(time(NULL));
    int cloudsCnt = rand() % maxCloudsCnt;

    // Устанавливаем минимальный порог количества облаков
    if ((cloudsCnt - minCloudsCnt) <= 0)
    {
        cloudsCnt = cloudsCnt + minCloudsCnt;
    }

    // Генерируем облака
    cloudList->clear();

    for (int i = 0; i < cloudsCnt; i++)
    {
        // Генерируем X-координату
        int cloudX = rand() % (skyWidth_ - static_cast<int>(texWidth_));
        // Генерируем Y-координату
        int cloudY = rand() % (skyHeight_ - static_cast<int>(texHeight_));
        // Генерируем вид облака
        int cloud = rand() % cloudsVersion;
        cloudList->emplace_back(static_cast<float>(cloudX), static_cast<float>(cloudY),
                                velocity, scale, opacity, cloud);
    }
}

void Sky::ReInitClouds()
{
    // Ренициализируем облака
    CloudInit(&cloudLayerOne, 5, 15, 0.1f, 0.5f, 125);
    CloudInit(&cloudLayerTwo, 3, 15, 0.2f, 1.f, 255);
    spritesList.clear();
    seconds_ = 0;
    isActed = false;
}

void Sky::DrawClouds(std::vector<Cloud> &cloudList, bool &isPause)
{
    if (cloudList.size() > 0)
    {

        for (Cloud &cld : cloudList)
        {
            if (!isPause)
            {
                cld.UpdatePosition();
            }

            if (cld.GetPosition().x > skyWidth_)
            {
                cld.SetPosition(0.f - texWidth_ * cld.GetScale(),
                                cld.GetPosition().y);
            }

            int curVerticalFrame_ = cld.GetID() / horizontalFrame_;
            int curHorizontalFrame_ = cld.GetID() - curVerticalFrame_ * horizontalFrame_;

            Rectangle sourceText{curHorizontalFrame_ * texWidth_,
                                 curVerticalFrame_ * texHeight_, texWidth_, texHeight_};

            Rectangle destText{cld.GetPosition().x, cld.GetPosition().y, texWidth_ * cld.GetScale(), texHeight_ * cld.GetScale()};
            DrawTexturePro(*texture_, sourceText, destText, {0.f, 0.f}, 0.f, {255, 255, 255, cld.GetOpacity()});
        }
    }
}

void Sky::AddSeagull()
{

    srand(time(NULL));
    int widthTex = 25;
    int varY = skyHeight_ / widthTex;
    float posX = skyWidth_ + widthTex;
    float posY = (rand() % varY) * widthTex;

    int variation = rand() % 20;
    float leftRight{1};

    if (variation < 10)
    {
        leftRight = -leftRight;
    }

    if (leftRight < 0)
    {
        posX = 0 - widthTex;
    }
    // spritesList.emplace_back(seagullTexture_, skyWidth_ + 25, posY, 25, 25, 60, 5);

    Sprite tmpSprite(seagullTexture_, posX, posY, widthTex, 25, 60, 5);
    tmpSprite.SetLeftRight(leftRight);
    tmpSprite.SetVelocityBySide();
    spritesList.emplace_back(tmpSprite);
}

void Sky::Tick(int frame, bool &isPause)
{
    srand(time(NULL));
    Timer(60, frame, seconds_);

    // Попытка вызова события кажды n секунд
    // Если пауза - игнорируем
    if (!isPause)
    {
        if (seconds_ % 20 == 0)
        {
            if (!isActed)
            {
                eventSeed = rand() % 20;
                if (eventSeed > 10)
                {
                    AddSeagull();
                    isActed = true;
                }
            }
        }
        else
        {
            isActed = false;
        }
    }

    DrawClouds(cloudLayerOne, isPause);

    if (spritesList.size() > 0)
    {
        for (Sprite &seagull : spritesList)
        {
            seagull.Tick(frame, isPause);
            if ((seagull.GetPosition().x < 0 - seagull.GetTexWidth() && seagull.GetLeftRight() > 0) ||
                (seagull.GetPosition().x > skyWidth_ + seagull.GetTexWidth() && seagull.GetLeftRight() < 0))
            {
                seagull.Die();
            }
        }
    }

    DrawClouds(cloudLayerTwo, isPause);

    // Удаление чаек
    spritesList.erase(std::remove_if(spritesList.begin(), spritesList.end(), [](Sprite &seagull)
                                     { return !(seagull.GetIsAlive()); }),
                      spritesList.end());
}

Sky::~Sky()
{
}
