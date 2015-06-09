#pragma once
#include "Graph.h"
#include <iostream>

class TownMap
{
	CrossPoint currentPosition;
	std::ostream& out;
	Graph towns;
public:

	TownMap(std::ostream& =std::cout);

	void deserialize(std::string fileName);
	void serialize(std::string fileName);

	void shortestPath(CrossPoint first, CrossPoint second);
	void shortestPathTo(CrossPoint second);

	void checkPath(CrossPoint first, CrossPoint second);
	void checkPathTo(CrossPoint second);

	void checkForCycle(CrossPoint vertex);
	void checkForCycle();

	void tellDeadends();
	void checkForEulerPath();

	void startRepairs(CrossPoint start, CrossPoint end);
	void endRepairs(CrossPoint start, CrossPoint end);

	bool validateCrossPoint(CrossPoint p) const { return towns.hasVertex(p); } 

	void goTo(CrossPoint next);

	int getNumberOfCrossRoads() const { return towns.size(); }
	CrossPoint getCurrent() const { return currentPosition; }
};

