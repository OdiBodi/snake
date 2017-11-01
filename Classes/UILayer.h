#pragma once

#include "cocos2d.h"
#include "Events.h"

class UILayer : public cocos2d::Layer, public IEvent
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init();

    // observer
    void onEvent(Event event, const void* value);

private:
    enum class Tag
    {
        TopLabel,
        StartButton,
    };
};