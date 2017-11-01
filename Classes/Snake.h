#pragma once

#include "cocos2d.h"
#include "Events.h"

class Snake : public cocos2d::Node, public IEvent
{
public:
    CREATE_FUNC(Snake);

    virtual bool init();

    // observer
    void onEvent(Event event, const void* value);

    void setApple(Node* apple);

private:
    enum class Tag
    {
        Head,
        Part
    };

    enum class Direction
    {
        Left,
        Right,
        Up,
        Down
    };

private:
    void reset();

    void addPart();
    void resetParts();

    void changeDirection(Direction dir);

    void setHeadPositionToCenter();

    bool checkHitWall();
    bool checkHeadCollision(Node* node);
    bool checkHeadWithPartsCollision();

private:
    int _size = 0;
    std::vector<cocos2d::Sprite*> _partsPool;

    cocos2d::Vec2 _movementOffset;
    Direction _movementDirection = Direction::Right;

    cocos2d::Node* _apple = nullptr;
};