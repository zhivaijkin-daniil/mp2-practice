#ifndef TLINK_H_
#define TLINK_H_

template <class TData>
class TLink
{
public:
	TData data;
	TLink<TData> *pNext;
};

#endif
