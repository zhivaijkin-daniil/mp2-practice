#include "TMonom.h"

TMonom::TNode()
{
    key = 0;
    data = 0;
    pNext = 0;
}


TMonom::TNode(const TMonom& tmp)
{
    key = tmp.key;
    data = tmp.data;
    pNext = tmp.pNext;
}

TMonom::TNode(unsigned int k, double d)
{
    key = k;
    data = d;
    pNext = 0;
}

const TMonom& TMonom::operator = (const TMonom& m)
{
    if (this != &m)
    {
        key = m.key;
        data = m.data;
    }
    return *this;
}

TMonom TMonom::operator + (const TMonom& m)
{
    if (key != m.key)
        throw Exception("Different degrees of monoms");
    return TMonom(key, data + m.data);
}

TMonom TMonom::operator - (const TMonom& m)
{
    if (key != m.key)
        throw Exception("Different degrees of monoms");
    return TMonom(key, data - m.data);
}

TMonom TMonom::operator * (const TMonom& m)
{
    if (((key / 100) + (m.key / 100) > 9)
        || (((key % 100) / 10) + ((m.key % 100) / 10) > 9)
        || (key % 10 + (m.key % 10) > 9))
        throw Exception("Monom not exist");
    return TMonom(key + m.key, data * m.data);
}

TMonom TMonom::operator += (const TMonom& m)
{
    *this = *this + m;
    return *this;
}

TMonom TMonom::operator -= (const TMonom& m)
{
    *this = *this - m;
    return *this;
}

TMonom TMonom::operator *= (const TMonom& m)
{
    *this = *this * m;
    return *this;
}

TMonom TMonom::operator -() const
{
    return TMonom(key, data * -1.);
}

TMonom TMonom::operator * (const double c)
{
    return TMonom(key, data * c);
}

bool TMonom::operator > (const TMonom& m)
{
    if (key > m.key)
        return true;
    return false;
}

bool TMonom::operator < (const TMonom& m)
{
    if (key < m.key)
        return true;
    return false;
}

bool TMonom::operator >= (const TMonom& m)
{
    if (key >= m.key)
        return true;
    return false;
}

bool TMonom::operator <= (const TMonom& m)
{
    if (key <= m.key)
        return true;
    return false;
}

bool TMonom::operator == (const TMonom& m)
{
    if (key == m.key && data == m.data)
        return true;
    return false;
}

bool TMonom::operator != (const TMonom& m)
{
    if (key == m.key && data != m.data)
        return true;
    return false;
}


