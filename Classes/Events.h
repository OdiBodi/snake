#pragma once

#include "Singleton.h"
#include <vector>

// observer
class IEvent
{
public:
    enum class Event
    {
        Game,
        GameOver,           // value(int) = snake size
        SnakeSizeChanged,   // value(int) = snake size
    };

public:
    virtual void onEvent(Event event, const void* value) = 0;
};

class Events : public Singleton<Events>
{
private:
    typedef std::pair<IEvent::Event, IEvent*> EventPair;

private:
    std::vector<EventPair> _events;

public:
    void notify(IEvent::Event event, void* value = nullptr); // if need, only allocate memory for value
    void notify(IEvent::Event event, int value);

    void add(IEvent::Event type, IEvent* event);    
    void remove(IEvent::Event type, IEvent* event);
};