#pragma once

#include "cocos2d.h"
#include "Events.h"

class Apple : public cocos2d::Sprite, public IEvent
{
public:
    CREATE_FUNC(Apple);

    virtual bool init();

    // observer
    void onEvent(Event event, const void* value);

private:
    void reposition();
};