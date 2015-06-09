#include "Vertex.h"

void Vertex::addInEdge(Edge* edge)
{
	if(edge!=NULL)
		inEdges.push_back(edge);
}

void Vertex::addOutEdge(Edge* edge)
{
	if(edge!=NULL)
		outEdges.push_back(edge);
}

void Vertex::removeInEdge(Edge* edge)
{
	if(edge!=NULL)
	{
		std::vector<Edge*>::const_iterator it = inEdges.begin();
		while(it != inEdges.end() && *it != edge)
			++it;
		if(it != inEdges.end())
			inEdges.erase(it);
	}
}

void Vertex::removeOutEdge(Edge* edge)
{
	if(edge!=NULL)
	{
		std::vector<Edge*>::const_iterator it = outEdges.begin();
		while(it != outEdges.end() && *it != edge)
			++it;
		if(it != outEdges.end())
			outEdges.erase(it);
	}
}


int Vertex::getDegreeIn() const
{
	int result = 0;
	for(int i=0; i < inEdges.size(); i++)
	{
		if(*inEdges[i])
			++result;
	}
	return result;
}

int Vertex::getDegreeOut() const
{
	int result = 0;
	for(int i=0; i < outEdges.size(); i++)
	{
		if(*outEdges[i])
			++result;
	}
	return result;
}