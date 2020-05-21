#ifndef _TNODE_H_
#define _TNODE_H_

#include <iostream>

using namespace std;

template <class TKey, class TData>
struct TNode
{
    TKey key;
    TData data;
    TNode* pNext;

    TNode();
    TNode(TKey, TData);
    TNode(const TNode<TKey, TData>&);
    ~TNode();

};

template <class TKey, class TData>
TNode<TKey, TData>::TNode()
{
    key = 0;
    data = 0;
    pNext = 0;
}

template <class TKey, class TData>
TNode<TKey, TData>::TNode(TKey k, TData d)
{
    key = k;
    data = d;
    pNext = 0;

}

template <class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& tmp)
{
    key = tmp.key;
    data = tmp.data;
    pNext = tmp.pNext;
}

template <class TKey, class TData>
TNode<TKey, TData>::~TNode()
{ }

#endif
