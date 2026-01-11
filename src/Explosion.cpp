#include "Explosion.h"
#include "Engine.h"

Explosion::Explosion(Texture2D *texture, float posX, float posY, float width, float height, float scale) : texture_(texture), explposionPos_({posX, posY}),
                                                                                                           explWidth_(width), explHeight_(height), scale_(scale)
{
    orign_ = {explWidth_ / 2, explHeight_ / 2};

    horizontalFrame_ = texture_->width / explWidth_;
    verticalFrame_ = texture_->height / explHeight_;

    endFrame = horizontalFrame_ * verticalFrame_;
}

void Explosion::Tick(int frame, bool &isPause)
{
    if (!isPause)
    {
        if (frame % 5 == 0 && explFrame < endFrame)
        {
            explFrame++;
        }
    }

    if (explFrame >= endFrame - 1)
    {
        isAlive = false;
    }

    curVerticalFrame_ = explFrame / horizontalFrame_;
    curHorizontalFrame_ = explFrame - curVerticalFrame_ * horizontalFrame_;

    // Rectangle sourceText{explFrame * explWidth_, 0.f, explWidth_, explHeight_};
    Rectangle sourceText{curHorizontalFrame_ * explWidth_, curVerticalFrame_ * explHeight_,
                         explWidth_, explHeight_};

    Rectangle destText{explposionPos_.x, explposionPos_.y, explWidth_ * scale_,
                       explHeight_ * scale_};
    DrawTexturePro(*texture_, sourceText, destText, orign_, 0.f, WHITE);

    // Линия по центру
    /*
    DrawLine(explposionPos_.x + horizontalFrame_ / 2, explposionPos_.y,
             explposionPos_.x + horizontalFrame_ / 2, explposionPos_.y + explHeight_, RED);

    DrawText(TextFormat("%i", explFrame), explposionPos_.x, explposionPos_.y, 25, RED);
    DrawText(TextFormat("%i", endFrame), explposionPos_.x + 50, explposionPos_.y, 25, RED);
    */
}

bool Explosion::GetIsAlive()
{
    return isAlive;
}

Explosion::~Explosion()
{
}
