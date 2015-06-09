#include "Graph.h"
#include <stack>
#include <queue>
#include <set>
#include <list>
#include <climits>
#include <algorithm>
#include <iostream>


Graph::Graph()
{
}



void Graph::addEdge(CrossPoint start, CrossPoint end, int len, bool repaired)
{
	Edge* p = new Edge(start,end,len,repaired);
	/*CrossPoint maxVertex = std::max(p->getStart(),p->getEnd());
	if(vertices.capacity() <= maxVertex)
	{
		int old = vertices.capacity();
		vertices.reserve(maxVertex+1);
		for(int i = old; i <= maxVertex; i++)
		{
			vertices.push_back(new Vertex());
		}
	}*/
	if(vertices.count(start) == 0)
	{
		vertices[start] = new Vertex();
	}
	if(vertices.count(end) == 0)
	{
		vertices[end] = new Vertex();
	}
	vertices[p->getStart()]->addOutEdge(p);
	vertices[p->getEnd()]->addInEdge(p);
}

bool Graph::hasVertex(CrossPoint p) const
{
	return vertices.count(p) > 0;
}

bool Graph::hasPath(CrossPoint start, CrossPoint end) const
{
	std::set<CrossPoint> visited;
	
	std::stack<CrossPoint> toVisit;
	toVisit.push(start);
	while(!toVisit.empty())
	{
		CrossPoint curr = toVisit.top();
		toVisit.pop();

		if(visited.count(curr)==0)
		{
			visited.insert(curr);
			for(int k=0; k < vertices.at(curr)->getDegreeOut(); k++)
			{
				Edge* tmp = vertices.at(curr)->getOutEdges()[k];
				if(*tmp)
					toVisit.push(tmp->getEnd());
			}
		}
	}
	bool result =  visited.count(end) != 0;
	return result;
}

bool Graph::hasCycle(CrossPoint vertex) const
{
	std::set<CrossPoint> visited;

	std::stack<std::pair<CrossPoint,CrossPoint>> toVisit;
	for(int i=0; i < vertices.at(vertex)->getDegreeOut(); i++)
	{
		Edge* tmp = vertices.at(vertex)->getOutEdges()[i];
		if(*tmp)
			toVisit.push(std::pair<CrossPoint,CrossPoint>(tmp->getEnd(),tmp->getStart()));
	}

	while(!toVisit.empty())
	{
		std::pair<CrossPoint,CrossPoint> curr = toVisit.top();
		toVisit.pop();

		if(visited.count(curr.first)==0)
		{
			if(curr.first != vertex)
			{
				visited.insert(curr.first);
				for(int k=0; k < vertices.at(curr.first)->getDegreeOut(); k++)
				{
					Edge* tmp = vertices.at(curr.first)->getOutEdges()[k];
					if(*tmp)
						toVisit.push(std::pair<CrossPoint,CrossPoint>(tmp->getEnd(),curr.first));
				}
			}
			else
			{
				if(curr.second != vertex)
				{
					return true;
				}
				Graph tmp = *this;
				Edge* problemEdge = tmp.findEdge(vertex,curr.first);
				problemEdge->putInRepairs(true);
				return tmp.hasPath(vertex,curr.first);

			}
		}
	}
	return false;
}

int Graph::countDeadends() const
{
	int counter = 0;
	for(std::hash_map<CrossPoint,Vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it)
		if(it->second->getDegreeOut() == 0)
			++counter;
	return counter;
}

Edge* Graph::findEdge(int start, int end) const
{
	std::vector<Edge*>& list = vertices.at(start)->getOutEdges();
	for(int i=0; i < list.size(); i++)
	{
		if(list[i]->getEnd() == end)
			return list[i];
	}
	return NULL;
}

bool Graph::hasEulerCycle() const
{
	for(std::hash_map<CrossPoint,Vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		Vertex* curr = it->second;
		if(curr->getDegreeIn() != curr->getDegreeOut())
			return false;
	}
	return true;
}

std::list<int> Graph::eulerCycle(CrossPoint start) const
{
	if(hasEulerCycle())
	{
		std::stack<CrossPoint> currentPath, wholePath;
		currentPath.push(start);
		while(!currentPath.empty())
		{
			CrossPoint next = currentPath.top();
			std::vector<Edge*>& tmp = vertices.at(next)->getOutEdges();
			int index = 0;
			while(index < tmp.size() && !(*tmp[index]))
				++index;
			if(index < tmp.size())
			{
				currentPath.push(tmp[index]->getEnd());
				tmp[index]->putInRepairs(true);
			}
			else
			{
				currentPath.pop();
				wholePath.push(next);
			}
		}
		std::list<CrossPoint> result;
		while(!wholePath.empty())
		{
			result.push_back(wholePath.top());
			wholePath.pop();
		}
		return result;
	}
	return std::list<CrossPoint>();
}

int Graph::minVertex(std::hash_map<CrossPoint,int>& distances, std::set<CrossPoint>& verticesLeft) const
{
	int min = INT_MAX;
	for(std::set<CrossPoint>::iterator it = verticesLeft.begin(); it != verticesLeft.end(); ++it)
	{
		if(min > distances[*it])
			min = *it;
	}
	return min;
}

std::list<Edge*> Graph::getShortestPaths(CrossPoint start, CrossPoint target,int& length) const
{
	std::set<CrossPoint> verticesLeft;
	std::hash_map<CrossPoint,Edge*> predecessors;
	std::hash_map<CrossPoint,int> distances;

	for(std::hash_map<CrossPoint,Vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		if(it->first==start)
		{
			predecessors[start] = NULL;
			distances[start]=0;
			continue;
		}
		predecessors[it->first] = NULL;
		distances[it->first] = INT_MAX;
		verticesLeft.insert(it->first);
	}
	std::vector<Edge*>& tmp = vertices.at(start)->getOutEdges();
	for(int j=0; j < tmp.size(); j++)
	{
		CrossPoint end = tmp[j]->getEnd();
		if(*tmp[j])
		{
			distances[end] = tmp[j]->getLength();
			predecessors[end] = tmp[j];
		}
	}
	CrossPoint nextToAdd;
	std::vector<Edge*> temp;
	while ( (nextToAdd = minVertex(distances,verticesLeft)) != INT_MAX)
	{
		verticesLeft.erase(nextToAdd);
		temp = vertices.at(nextToAdd)->getOutEdges();
		for(int j=0; j < temp.size(); j++)
		{
			CrossPoint end = temp[j]->getEnd();
			int newLen = distances[nextToAdd] + temp[j]->getLength();
			if(*temp[j] && newLen < distances[end])
			{
				distances[end] = newLen;
				predecessors[end] = temp[j];
			}
		}
	}
	if(verticesLeft.count(target) != 0)
	{
		return std::list<Edge*>();
	}
	std::list<Edge*> result;
	CrossPoint startIndex = target;
	length = 0;
	while(target != start)
	{
		result.push_front(predecessors[target]);
		length += predecessors[target]->getLength();
		target = predecessors[target]->getStart();
	}
	return result;
}


/*int Graph::calculatePathLength(std::list<CrossPoint>& path) const
{
	if(path.size() == 0)
		return 0;
	int length = 0;
	std::list<CrossPoint>::iterator it = path.begin();
	std::list<CrossPoint>::iterator next = path.begin();
	++next;
	if(next==path.end())
	{
		return 0;
	}
	while(next != path.end())
	{
		Edge* curr = findEdge(*it,*next);
		length += curr->getLength();
		++it;
		++next;
	}
	return length;
}

bool Graph::comparePaths(std::list<CrossPoint>* first,std::list<CrossPoint>* second) const
{
	return calculatePathLength(*first) < calculatePathLength(*second);
}

void Graph::findMinPaths(CrossPoint first, CrossPoint second, std::ostream& os)
{
	std::list<CrossPoint> path;
	std::vector<std::list<CrossPoint>*> paths;
	findAllPathsHelper(first,second,path,paths);
	std::sort(paths.begin(),paths.end(),&Graph::comparePaths);
	for(int i=0; i < 3 && i < paths.size() ; i++)
	{
		printPath(*paths[i],os);
	}
}

void Graph::printPath(std::list<CrossPoint>& first, std::ostream& os) const
{
	for(std::list<CrossPoint>::iterator it = first.begin(); it != first.end(); ++it)
	{
		os << (*it) << ' ';
	}
	os << std::endl;
}

void Graph::findAllPathsHelper(CrossPoint first,CrossPoint last,std::list<CrossPoint>& path,
								std::vector<std::list<CrossPoint>*>& paths)
{
	path.push_back(first);
	if(first == last)
	{
		paths.push_back(new std::list<CrossPoint>(path));
	}
	else
	{
		for(int i=0; i < vertices.at(first)->getOutEdges().size(); i++)
		{
			CrossPoint p = vertices.at(first)->getOutEdges()[i]->getEnd();
			if( std::find(path.begin(),path.end(),p) != path.end())
				findAllPathsHelper(p,last,path,paths);
		}
	}
	path.pop_back();
}*/

Graph::Graph(Graph const& other)
{
	copy(other);
}

Graph& Graph::operator=(Graph const& other)
{
	if(this!=&other)
	{
		clean();
		copy(other);
	}
	return *this;
}

Graph::~Graph()
{
	clean();
}

std::ostream& operator<<(std::ostream& os, Graph const& graph)
{
	for(std::hash_map<CrossPoint,Vertex*>::const_iterator it = graph.vertices.begin(); it != graph.vertices.end(); ++it)
	{
		std::vector<Edge*>& tmp = it->second->getOutEdges();
		os << it->first;
		for(int j=0; j < tmp.size(); j++)
		{
			os << ' ' << tmp[j]->getEnd() << ' ' << tmp[j]->getLength();
		}
		os << std::endl;
	}
	return os;
}


void Graph::clean()
{
	for(std::hash_map<CrossPoint,Vertex*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		for(int j=0; j < it->second->getDegreeOut(); j++)
			delete it->second->getOutEdges()[j];
		delete it->second;
	}

}

void Graph::copy(Graph const& other)
{
	for(std::hash_map<CrossPoint,Vertex*>::const_iterator it = other.vertices.begin(); it != other.vertices.end(); ++it)
	{
		std::vector<Edge*>& tmp = it->second->getOutEdges();
		for(int j=0; j < tmp.size(); j++)
		{
			this->addEdge(tmp[j]->getStart(),tmp[j]->getEnd(),tmp[j]->getLength(),!(*tmp[j]));
		}
	}
}