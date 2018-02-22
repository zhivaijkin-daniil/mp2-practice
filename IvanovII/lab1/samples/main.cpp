#include "tlink.h"

int main()
{
	TLink<char> link;
	link.data = 'c';
	link.pNext = 0;
	return 0;
}
