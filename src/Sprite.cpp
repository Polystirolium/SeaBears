#include "Sprite.h"

Sprite::Sprite(Texture2D *texture, float posX, float posY,
               float texWidth, float texHeight, int id) : texture_(texture), position_({posX, posY}),
                                                          texWidth_(texWidth), texHeight_(texHeight),
                                                          horizontalFrame_(texture_->width / texWidth_),
                                                          verticalFrame_(texture_->height / texHeight_),
                                                          maxFrames_(horizontalFrame_ * verticalFrame_),
                                                          id_(id)
{
    animated_ = false;
}

Sprite::Sprite(Texture2D *texture, float posX, float posY, float texWidth,
               float texHeight, int fps, int frameDivider) : texture_(texture), position_({posX, posY}),
                                                             texWidth_(texWidth), texHeight_(texHeight),
                                                             frameDivider_(frameDivider),
                                                             horizontalFrame_(texture_->width / texWidth_),
                                                             verticalFrame_(texture_->height / texHeight_),
                                                             maxFrames_(horizontalFrame_ * verticalFrame_)

{

    animated_ = true;
}

void Sprite::Tick()
{
    int curVerticalFrame_ = id_ / horizontalFrame_;
    int curHorizontalFrame_ = id_ - curVerticalFrame_ * horizontalFrame_;

    Rectangle sourceText{curHorizontalFrame_ * texWidth_,
                         curVerticalFrame_ * texHeight_, texWidth_, texHeight_};

    Rectangle destText{position_.x, position_.y, texWidth_ * scale_ * leftRight_, texHeight_ * scale_};
    DrawTexturePro(*texture_, sourceText, destText, {0.f, 0.f}, 0.f, WHITE);
}

void Sprite::Tick(int frame, bool &isPause)
{
    if (frameDivider_ != 0 && !isPause)
    {
        if (frame % frameDivider_ == 0)
        {
            curFrame_++;
        }
    }
    int curVerticalFrame_ = curFrame_ / horizontalFrame_;
    int curHorizontalFrame_ = curFrame_ - curVerticalFrame_ * horizontalFrame_;

    Rectangle sourceText{curHorizontalFrame_ * texWidth_,
                         curVerticalFrame_ * texHeight_, texWidth_ * leftRight_, texHeight_};

    Rectangle destText{position_.x, position_.y,
                       texWidth_ * scale_, texHeight_ * scale_};
    DrawTexturePro(*texture_, sourceText, destText, {0.f, 0.f}, 0.f, WHITE);

    if ((curFrame_ < 4 && velocity_.y > 0) || (curFrame_ > 3 && velocity_.y < 0))
    {
        velocity_.y = -velocity_.y;
    }

    if (!isPause)
    {
        position_ = Vector2Add(position_, velocity_);
    }

    if (repeatable && curFrame_ >= maxFrames_)
    {
        curFrame_ = 0;
    }
}

void Sprite::Die()
{
    isAlive = false;
}

void Sprite::SetLeftRight(float leftRight)
{
    leftRight_ = leftRight;
}

Vector2 Sprite::GetVelocity()
{
    return velocity_;
}

Vector2 Sprite::GetPosition()
{
    return position_;
}

float Sprite::GetTexWidth()
{
    return texWidth_;
}

float Sprite::GetLeftRight()
{
    return leftRight_;
}

void Sprite::SetVelocity(Vector2 velocity)
{
    velocity_ = velocity;
}

void Sprite::SetVelocityBySide()
{
    velocity_ = {velocity_.x * leftRight_, velocity_.y};
}

bool Sprite::GetIsAlive()
{
    return isAlive;
}

Sprite::~Sprite()
{
}
