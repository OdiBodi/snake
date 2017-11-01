#include "UILayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getWinSize();

    // top label
    auto label = Label::createWithTTF("snake", "arial.ttf", 24);
    if (label == nullptr)
    {
        return false;
    }
    else
    {
        label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
        addChild(label, 1, static_cast<int>(Tag::TopLabel));
    }

    // start button
    auto button = ui::Button::create("button_normal.png", "button_press.png", "button_disable.png");
    button->setTitleFontName("arial.ttf");
    button->setTitleText("Start");
    button->setTitleFontSize(20.f);
    button->setTitleColor(Color3B::RED);
    button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::ENDED:
            {
                Events::instance().notify(IEvent::Event::Game);
            }
            break;
        }
    });
    addChild(button, 1, static_cast<int>(Tag::StartButton));

    // events
    Events::instance().add(IEvent::Event::Game, this);
    Events::instance().add(IEvent::Event::GameOver, this);
    Events::instance().add(IEvent::Event::SnakeSizeChanged, this);

    return true;
}

void UILayer::onEvent(Event event, const void* value)
{
    auto topLabel = getChildByTag<Label*>(static_cast<int>(Tag::TopLabel));

    switch (event)
    {
        case IEvent::Event::Game:
        {
            topLabel->setString("snake size is 1");

            auto startButton = getChildByTag<ui::Button*>(static_cast<int>(Tag::StartButton));
            startButton->setVisible(false);
        }
        break;

        case IEvent::Event::GameOver:
        {
            int snakeSize = *static_cast<const int*>(value);

            std::stringstream ss;
            ss << "game over!\nsnake size is " << snakeSize;
            topLabel->setString(ss.str());

            auto startButton = getChildByTag<ui::Button*>(static_cast<int>(Tag::StartButton));
            startButton->setVisible(true);
        }
        break;

        case IEvent::Event::SnakeSizeChanged:
        {
            int snakeSize = *(int*)(value);

            std::stringstream ss;
            ss << "snake size is " << snakeSize;
            topLabel->setString(ss.str());
        }
        break;
    }    
}