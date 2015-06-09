#pragma once

typedef int CrossPoint;

class Edge
{
	CrossPoint start;
	CrossPoint end;
	int length;
	bool inRepairs;
public:
	Edge(CrossPoint,CrossPoint,int,bool =false);

	CrossPoint getStart() const { return start; }
	CrossPoint getEnd() const { return end; }
	int getLength() const { return length; }
	
	void putInRepairs(bool isInRepairs) { inRepairs = isInRepairs; }
	operator bool() { return !inRepairs; }

	void setLength(int); 
	
};

