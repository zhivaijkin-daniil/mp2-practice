#pragma once

template <class T>
class TLink
{
public:
    T data;
    TLink<T>* pNext;
};
