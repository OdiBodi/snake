#include "HelloWorldScene.h"
#include "UILayer.h"
#include "GameLayer.h"

USING_NS_CC;

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto ui = UILayer::create();
    auto game = GameLayer::create();
    addChild(ui, 2, static_cast<int>(Tag::UILayer));
    addChild(game, 1, static_cast<int>(Tag::GameLayer));

    return true;
}