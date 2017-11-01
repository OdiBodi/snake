#pragma once

template<class T> class Singleton
{
public:
    static T& instance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    Singleton(T const&) = delete;
    T& operator= (T const&) = delete;
};