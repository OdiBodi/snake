#pragma once

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GameLayer);

    virtual bool init();

private:
    enum class Tag
    {
        Apple,
        Snake
    };
};