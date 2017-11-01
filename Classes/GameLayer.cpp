#include "GameLayer.h"
#include "Apple.h"
#include "Snake.h"

USING_NS_CC;

bool GameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto apple = Apple::create();
    if (apple == nullptr)
    {
        return false;
    }
    addChild(apple, 1, static_cast<int>(Tag::Apple));

    auto snake = Snake::create();
    if (snake == nullptr)
    {
        return false;
    }
    addChild(snake, 1, static_cast<int>(Tag::Snake));

    snake->setApple(apple);

    return true;
}