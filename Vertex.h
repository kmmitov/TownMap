#pragma once
#include "Edge.h"
#include <vector>
class Vertex
{
	std::vector<Edge*> inEdges;
	std::vector<Edge*> outEdges;
public:
	
	void addInEdge(Edge*);
	void addOutEdge(Edge*);
	void removeOutEdge(Edge*);
	void removeInEdge(Edge*);

	std::vector<Edge*>& getOutEdges() { return outEdges; }

	int getDegreeIn() const;
	int getDegreeOut() const;

};

