#include "Snake.h"

USING_NS_CC;

bool Snake::init()
{
    if (!Node::init())
    {
        return false;
    }

    // keyboard listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
    {
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            {
                changeDirection(Direction::Left);
            }
            break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            {
                changeDirection(Direction::Right);
            }
            break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            {
                changeDirection(Direction::Up);
            }
            break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            {
                changeDirection(Direction::Down);
            }
            break;
            /*case EventKeyboard::KeyCode::KEY_SPACE:
            {
                addPart();
            }
            break;*/
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // events
    Events::instance().add(IEvent::Event::Game, this);
    Events::instance().add(IEvent::Event::GameOver, this);

    return true;
}

void Snake::onEvent(Event event, const void* value)
{
    switch (event)
    {
        case IEvent::Event::Game:
        {
            reset();
        }
        break;

        case IEvent::Event::GameOver:
        {
            unschedule("snake_movement");
        }
        break;
    }
}

void Snake::setApple(Node* apple)
{
    _apple = apple;
}

void Snake::reset()
{
    resetParts();
    changeDirection(Direction::Right);

    // movement animation
    schedule([=](float dt)
        {
            auto head = _partsPool[0];
            Vec2 prevPos = head->getPosition();

            // head
            auto hpos = head->getPosition() + _movementOffset;
            head->setPosition(hpos);

            // parts
            for (int i = 1; i < _size; ++i)
            {
                auto tmp = _partsPool[i]->getPosition();
                _partsPool[i]->setPosition(prevPos);
                prevPos = tmp;
            }

            if (checkHitWall() || checkHeadWithPartsCollision())
            {
                Events::instance().notify(IEvent::Event::GameOver, _size);
                return;
            }
            if (checkHeadCollision(_apple))
            {
                addPart();
            }
        },
        0.5f, // animation speed
        "snake_movement"
    );
}

void Snake::addPart()
{
    if (_partsPool.empty())
    {
        // add head
        auto head = Sprite::create("snake_head.png");
        addChild(head, 2, static_cast<int>(Tag::Head));
        _partsPool.push_back(head);

        _size = 1;

        setHeadPositionToCenter();
    }
    else
    {
        Sprite* part = nullptr;

        if (_size++ >= _partsPool.size())
        {
            part = Sprite::create("snake_part.png");
            addChild(part, 1, static_cast<int>(Tag::Part));
            _partsPool.push_back(part);
        }
        else // part in pool
        {
            part = _partsPool[_size - 1];
            part->setVisible(true);
        }

        auto pos = _partsPool[_size - 2]->getPosition() - _movementOffset;
        part->setPosition(pos);

        Events::instance().notify(IEvent::Event::SnakeSizeChanged, _size);
    }
}

void Snake::resetParts()
{
    if (_partsPool.empty())
    {
        addPart();
    }
    else // reset pool objects
    {
        setHeadPositionToCenter();        

        // hide parts
        for (int i = 1; i < _partsPool.size(); ++i)
        {
            _partsPool[i]->setVisible(false);
        }

        _size = 1;

        Events::instance().notify(IEvent::Event::SnakeSizeChanged, _size);
    }
}

void Snake::changeDirection(Direction dir)
{
    auto  head = _partsPool[0];
    auto& size = head->getContentSize();

    _movementDirection = dir;

    switch (dir)
    {
        case Direction::Left:
        {
            head->setRotation(180.f);
            _movementOffset.x = -(size.width + 1);
            _movementOffset.y = 0.f;
        }
        break;

        case Direction::Right:
        {
            head->setRotation(0.f);
            _movementOffset.x = (size.width + 1);
            _movementOffset.y = 0.f;
        }
        break;

        case Direction::Up:
        {
            head->setRotation(-90.f);
            _movementOffset.x = 0.f;
            _movementOffset.y = (size.height + 1);
        }
        break;

        case Direction::Down:
        {
            head->setRotation(90.f);
            _movementOffset.x = 0.f;
            _movementOffset.y = -(size.height + 1);
        }
        break;
    }
}

void Snake::setHeadPositionToCenter()
{
    auto visibleSize = Director::getInstance()->getWinSize();
    _partsPool[0]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}

bool Snake::checkHitWall()
{
    auto headPosition = _partsPool[0]->getPosition();

    auto& visibleSize = Director::getInstance()->getWinSize();
    Rect  visibleRect(0.f, 0.f, visibleSize.width, visibleSize.height);

    return !visibleRect.containsPoint(headPosition);
}

bool Snake::checkHeadCollision(Node* object)
{
    auto headBB = _partsPool[0]->getBoundingBox();
    auto objectBB = object->getBoundingBox();
    return headBB.intersectsRect(objectBB);
}

bool Snake::checkHeadWithPartsCollision()
{
    for (int i = 1; i < _size; ++i)
    {
        auto part = _partsPool[i];
        if (checkHeadCollision(part))
        {
            return true;
        }
    }
    return false;
}