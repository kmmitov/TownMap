#include "TownMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

TownMap::TownMap(std::ostream& os)
	:out(os),currentPosition(0)
{

}

void TownMap::deserialize(std::string fileName)
{
	towns = Graph();
	std::ifstream in(fileName,std::ios::in);
	std::string line;
	int startVertex = -1;
	while(std::getline(in,line))
	{
		std::stringstream stream(line);
		stream >> startVertex;
		int endVertex, length;
		while(stream >> endVertex)
		{
			stream >> length;
			towns.addEdge(startVertex,endVertex,length);
		}
	}
	currentPosition = startVertex;
	in.close();
}

void TownMap::serialize(std::string fileName)
{
	std::ofstream out(fileName,std::ios::out);
	out << towns;
	out.close();
}

void TownMap::shortestPath(CrossPoint first, CrossPoint second)
{
	int length = 0;
	std::list<Edge*> vertices = towns.getShortestPaths(first,second,length);
	if(vertices.size() == 0)
	{
		out << "No path exists, sorry! " << std::endl;
		return;
	}
	std::list<Edge*>::iterator it = vertices.begin();
	out << "The shortest path comprises the following: " << std::endl;
	for(; it != vertices.end(); ++it)
	{
		Edge* curr =*it;
		out << "Street from " << curr->getStart() << " to " << curr->getEnd() << ", distance: " << curr->getLength() << std::endl;
	}
	out << "Total length of shortest path: " << length << std::endl;
}

void TownMap::shortestPathTo(CrossPoint other)
{
	shortestPath(currentPosition,other);
	goTo(other);
}

void TownMap::checkPath(CrossPoint first, CrossPoint second)
{
	bool hasPath = towns.hasPath(first,second);
	out << (hasPath?"There exists a path between these locations":"There does not exist a path between these locations") << std::endl;
}

void TownMap::checkPathTo(CrossPoint other)
{
	checkPath(currentPosition,other);
}

void TownMap::checkForCycle(CrossPoint cross) 
{
	bool hasCycle = towns.hasCycle(cross);
	out << (hasCycle?"There exists a cycle through this vertex":"No tour through this vertex is possible") << std::endl;
}

void TownMap::checkForCycle()
{
	checkForCycle(currentPosition);
}

void TownMap::tellDeadends()
{
	int number = towns.countDeadends();
	out << "There are " << number << " deadend streets in this town" << std::endl;
}

void TownMap::checkForEulerPath()
{
	Graph townsCpy = towns;
	std::list<CrossPoint> path = townsCpy.eulerCycle(currentPosition);
	if(path.empty())
	{
		out << "A tour of all streets without repetitions is not possible, sorry" << std::endl;
	}
	else
	{
		out << "A tour of all streets without repetitions is possible in the following order: " << std::endl;
		std::list<CrossPoint>::iterator it = path.begin();
		for(;it!=path.end();++it)
		{
			out << *it << " ";
		}
		out << std::endl;
	}
}

void TownMap::startRepairs(CrossPoint start, CrossPoint end) 
{
	Edge* toRepair = towns.findEdge(start,end);
	toRepair->putInRepairs(true);
}

void TownMap::endRepairs(CrossPoint start, CrossPoint end)
{
	Edge* toRepair = towns.findEdge(start,end);
	toRepair->putInRepairs(false);
}

void TownMap::goTo(CrossPoint next)
{
	if(towns.hasPath(currentPosition,next))
		currentPosition = next;
	else
		std::cerr << "Can't change position! No path exists between this two positions!" << std::endl; 
}