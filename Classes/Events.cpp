#include "Events.h"
#include <algorithm>

void Events::notify(IEvent::Event event, void* value)
{
    for each (auto& e in _events)
    {
        if (e.first == event)
        {
            e.second->onEvent(event, value);
        }
    }

    if (value != nullptr)
    {
        delete value;
    }
}

void Events::notify(IEvent::Event event, int value)
{
    int* val = new int(value);
    notify(event, val);
}

void Events::add(IEvent::Event type, IEvent* event)
{
    if (event != nullptr)
    {
        auto it = std::find_if(_events.begin(), _events.end(),
            [=](const auto& e)
            {
                return (e.first == type) && (e.second == event);
            }
        );
        if (it == _events.end())
        {
            auto pair = std::make_pair(type, event);
            _events.push_back(pair);
        }
    }
}

void Events::remove(IEvent::Event type, IEvent* event)
{
    if (event != nullptr)
    {
        auto it = std::remove_if(_events.begin(), _events.end(),
            [=](const auto& e)
            { 
                return (e.first == type) && (e.second == event);
            }
        );
        _events.erase(it, _events.end());
    }
}