#include "Edge.h"


Edge::Edge(CrossPoint start , CrossPoint end, int len, bool repaired)
	:inRepairs(repaired)
{
	if(start >= 0 && end >= 0 && len > 0)
	{
		this->start = start;
		this->end = end;
		this->length = len;
	}
}

void Edge::setLength(int newLength)
{
	if(newLength > 0)
	{
		this->length = newLength;
	}
}

