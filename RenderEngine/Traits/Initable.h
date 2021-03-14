#pragma once

template<class T>
class IInitable
{
public:
    void Init()
    {
        T::Init();
    }
};
