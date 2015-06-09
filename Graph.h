#pragma once
#include <hash_map>
#include <list>
#include <set>
#include <hash_map>
#include "Vertex.h"


class Graph
{
	std::hash_map<CrossPoint,Vertex*> vertices;
public:
	Graph();
	Graph(Graph const&);
	Graph& operator=(Graph const&);
	~Graph();

	void addEdge(CrossPoint,CrossPoint,int,bool =false);

	std::list<Edge*> getShortestPaths(CrossPoint,CrossPoint,int&) const;
	bool hasPath(CrossPoint,CrossPoint) const;
	bool hasCycle(CrossPoint) const;
	int  countDeadends() const;
	
	bool hasEulerCycle() const;
	std::list<int> eulerCycle(CrossPoint) const;

	bool hasVertex(CrossPoint) const;
	Edge* findEdge(CrossPoint start, CrossPoint end) const;

	//void findMinPaths(CrossPoint,CrossPoint,std::ostream&);

	int size() const { return vertices.size(); }

	friend std::ostream& operator<<(std::ostream& os, Graph const&);
private:
	void clean();
	void copy(Graph const&);
	int minVertex(std::hash_map<CrossPoint,int>&,std::set<CrossPoint>&) const;
	/*bool comparePaths(std::list<CrossPoint>*,std::list<CrossPoint>*) const;
	int calculatePathLength(std::list<CrossPoint>&) const;
	void printPath(std::list<CrossPoint>&,std::ostream&) const;
	void findAllPathsHelper(CrossPoint,CrossPoint,std::list<CrossPoint>& path,
								std::vector<std::list<CrossPoint>*>& paths);*/
};

