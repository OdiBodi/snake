#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    CREATE_FUNC(HelloWorld);

    virtual bool init();

private:
    enum class Tag
    {
        UILayer,
        GameLayer,
    };
};