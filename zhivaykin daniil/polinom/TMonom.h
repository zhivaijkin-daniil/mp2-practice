#ifndef _TMONOM_H_
#define _TMONOM_H_

#include <iostream>
#include "TNode.h"
#include "Exception.h"

using namespace std;

#define TMonom TNode<unsigned int, double>
#define MAX_KEY 999
#define MAX_DEG 9

template<>
struct TMonom
{
    unsigned int key;
    double data;
    TMonom* pNext;

    TNode();
    TNode(const TMonom&);
    TNode(unsigned int, double);
    ~TNode() { };

    friend ostream& operator<<(ostream& out, const TMonom* m)
    {
        if (m->key == 0)
        {
            out << m->data;
            return out;
        }
        if (m->data != 1)
            if (m->data != -1)
                out << m->data;
            else out << '-';
        if (m->key / 100 > 0)
            if (m->key / 100 == 1)
                out << 'x';
            else
                out << "x^" << (m->key / 100);
        if ((m->key % 100) / 10 > 0)
            if ((m->key % 100) / 10 == 1)
                out << 'y';
            else
                out << "y^" << ((m->key % 100) / 10);
        if (m->key % 10 > 0)
            if (m->key % 10 == 1)
                out << 'z';
            else
                out << "z^" << (m->key % 10);
        return out;
    }

    TMonom operator + (const TMonom&);
    TMonom operator - (const TMonom&);
    TMonom operator * (const TMonom&);
    const TMonom& operator = (const TMonom&);

    TMonom operator += (const TMonom&);
    TMonom operator -= (const TMonom&);
    TMonom operator *= (const TMonom&);

    TMonom operator -() const;
    TMonom operator * (const double);

    bool operator > (const TMonom&);
    bool operator >= (const TMonom&);
    bool operator < (const TMonom&);
    bool operator <= (const TMonom&);
    bool operator == (const TMonom&);
    bool operator != (const TMonom&);
};
#endif