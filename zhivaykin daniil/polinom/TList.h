#ifndef _TLIST_H_
#define _TLIST_H_

#include "TNode.h"
#include <iostream>
#include "Exception.h"

using namespace std;

template <class TKey, class TData>
class TList
{
protected:
    TNode<TKey, TData>* pFirst;
    TNode<TKey, TData>* pCurr;
    TNode<TKey, TData>* pNext;
    TNode<TKey, TData>* pPrev;

public:
    TList();
    TList(const TList&);
    TList(TNode<TKey, TData>*);
    ~TList();

    void Reset();
    void Next();

    TNode<TKey, TData>* Search(TKey);
    TNode<TKey, TData>* Current();

    void InsertB(TKey, TData);
    void InsertE(TKey, TData);
    void InsertE(TNode<TKey, TData>&);
    void InsertAfter(TKey, TKey, TData);
    void InsertBefore(TKey, TKey, TData);


    void Delete(TKey);

    bool IsFull() const;
    bool IsEmpty() const;


    template <typename TKey, typename TData>
    friend ostream& operator<<(ostream& out, const TList<TKey, TData>& l)
    {
        if (l.pFirst == 0)
        {
            out << "Error, empty list" << endl;
            return out;
        }
        TNode<TKey, TData>* tmp = l.pFirst;
        while (tmp != 0)
        {
            out << tmp << ' ';
            tmp = tmp->pNext;
        }
        return out;
    }
};

template <class TKey, class TData>
TList<TKey, TData>::TList()
{
    pFirst = 0;
    pPrev = 0;
    pNext = 0;
    pCurr = 0;
}

template <class TKey, class TData>
TList<TKey, TData>::TList(const TList& tmp2)
{
    if (tmp2.pFirst == 0)
    {
        pFirst = 0;
        pPrev = 0;
        pNext = 0;
        pCurr = 0;
    }
    else
    {
        pFirst = new TNode<TKey, TData>(*(tmp2.pFirst));
        pPrev = 0;
        pCurr = pFirst;
        pNext = pFirst->pNext;
        TNode<TKey, TData>* tmp1(pFirst);
        TNode<TKey, TData>* tmp(tmp2.pFirst);
        while (tmp->pNext != 0)
        {
            tmp1->pNext = new TNode<TKey, TData>(*(tmp->pNext));
            tmp = tmp->pNext;
            tmp1 = tmp1->pNext;
        }
        tmp1->pNext = 0;
    }
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* first)
{
    pFirst = first;
    pPrev = 0;
    pCurr = pFirst;
    pNext = pFirst->pNext;
}

template <class TKey, class TData>
TList<TKey, TData>::~TList()
{
    while (pFirst != 0)
    {
        pNext = pFirst->pNext;
        delete pFirst;
        pFirst = pNext;
    }
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key1)
{
    TNode<TKey, TData>* first = pFirst;

    if (pFirst == 0)
        throw exception("Your list is empty");

    while (first != 0 && first->key != key1)
        first = first->pNext;

    if (first == 0)
        throw exception("Key not found");

    return first;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertB(TKey key, TData data)
{
    if (pFirst == 0)
    {
        pFirst = new TNode<TKey, TData>(key, data);
        pCurr = pFirst;
        return;
    }

    TNode<TKey, TData>* node = new TNode<TKey, TData>(key, data);
    node->pNext = pFirst;
    pFirst = node;
    if (pCurr == 0)
        pCurr = pFirst;
    if (pCurr == pFirst->pNext)
        pPrev = pFirst;
    return;
}


template <class TKey, class TData>
void TList<TKey, TData>::InsertE(TKey key, TData data)
{
    if (pFirst == 0)
    {
        pFirst = new TNode<TKey, TData>(key, data);
        pCurr = pFirst;
        return;
    }
    TNode<TKey, TData>* node = new TNode<TKey, TData>(key, data);
    TNode<TKey, TData>* tmp = pFirst;
    while (tmp->pNext != 0)
    {
        tmp = tmp->pNext;
    }
    tmp->pNext = node;
    if (pCurr == tmp)
        pNext = node;
    if (tmp == pPrev)
        pPrev = tmp->pNext;

}

template <class TKey, class TData>
void TList<TKey, TData>::InsertE(TNode<TKey, TData>& node)
{
    InsertE(node.key, node.data);
    return;
}


template <class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey key1, TKey key2, TData data)
{
    if (pFirst == 0)
    {
        throw exception("Empty");
        return;
    }
    TNode<TKey, TData>* tmp = pFirst;
    while ((tmp != 0) && (tmp->key != key1))
    {
        tmp = tmp->pNext;
    }
    if (tmp == 0)
        throw exception("Key not found");
    TNode<TKey, TData>* tmp1 = tmp->pNext;
    TNode<TKey, TData>* node = new TNode<TKey, TData>(key2, data);
    node->pNext = tmp1;
    tmp1 = node;
    if (node->pNext == pCurr)
        pPrev = node;
    if (tmp == pCurr)
        pNext = node;
}


template <class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey key1, TKey key2, TData data)
{
    if (pFirst == 0)
    {
        throw exception("Empty");
        return;
    }
    if (pFirst->key == key1)
    {
        InsertB(key2, data);
        return;
    }
    TNode<TKey, TData>* tmp = pFirst;
    while ((tmp->pNext != 0) && (tmp->pNext->key != key1))
        tmp = tmp->pNext;
    if (tmp->pNext == 0)
        throw exception("Key not found");
    TNode<TKey, TData>* tmp1 = tmp->pNext;
    TNode<TKey, TData>* node = new TNode<TKey, TData>(key2, data);
    node->pNext = tmp1;
    tmp1 = node;
    if (pCurr == tmp)
        pNext = node;
    if (node->pNext == pCurr)
        pPrev = node;
}


template <class TKey, class TData>
void TList<TKey, TData>::Delete(TKey key1)
{
    if (pFirst == 0)
    {
        throw exception("Empty");
        return;
    }
    if (pFirst->key == key1)
    {
        TNode<TKey, TData>* tmp = pFirst->pNext;
        if (pCurr == pFirst)
        {
            pCurr = pNext;
            if (pNext != 0)
                pNext = pNext->pNext;
        }
        if (pPrev == pFirst)
            pPrev = 0;
        delete pFirst;
        pFirst = tmp;
        return;
    }
    TNode<TKey, TData>* tmp1 = pFirst;
    while ((tmp1->pNext != 0) && (tmp1->pNext->key != key1))
        tmp1 = tmp1->pNext;
    if (tmp1->pNext == 0)
        throw exception("Key not found");

    TNode<TKey, TData>* del = tmp1->pNext->pNext;
    if (pPrev == tmp1->pNext)
        pPrev = tmp1;
    if (pCurr == tmp1->pNext)
    {
        pCurr = pNext;
        if (pNext != 0)
            pNext = pNext->pNext;
    }
    if (pNext == tmp1->pNext)
        pNext = pNext->pNext;
    delete tmp1->pNext;
    tmp1->pNext = del;
}

template <class TKey, class TData>
void TList<TKey, TData>::Reset()
{
    if (pFirst == 0)
    {
        throw exception("Empty");
        return;
    }
    pPrev = 0;
    pCurr = pFirst;
    pNext = pFirst->pNext;
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsFull() const
{
    return (pCurr == 0);
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEmpty() const
{
    return (pFirst == 0);
}

template <class TKey, class TData>
void TList<TKey, TData>::Next()
{
    if (IsFull())
        throw exception("The end of list");
    pPrev = pCurr;
    pCurr = pNext;
    if (pNext != 0)
        pNext = pNext->pNext;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Current()
{
    return pCurr;
}

#endif
