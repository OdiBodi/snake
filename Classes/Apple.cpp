#include "Apple.h"

USING_NS_CC;

bool Apple::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    setTexture("apple.png");
    setVisible(false);

    // events
    Events::instance().add(IEvent::Event::Game, this);
    Events::instance().add(IEvent::Event::SnakeSizeChanged, this);

    return true;
}

void Apple::onEvent(Event event, const void* value)
{
    switch (event)
    {
        case IEvent::Event::Game:
        case IEvent::Event::SnakeSizeChanged:
        {
            reposition();
        }
        break;
    }
}

void Apple::reposition()
{
    auto director = Director::getInstance();

    auto visibleSize = director->getWinSize();
    auto contentSize = getContentSize();

	setPosition(Vec2
        (
	    	random(contentSize.width, visibleSize.width - contentSize.width),
	    	random(contentSize.height, visibleSize.height - contentSize.height)
        )
    );

    setVisible(true);
}