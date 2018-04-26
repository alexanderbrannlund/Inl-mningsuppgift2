#include "Graph.h"
#include<string>
#include <sstream>
#include<iostream>

bool Graph::addingArc(int sourceVertex, int destinationVertex, int arcWeight)
{
	bool added = false;
	AdjacencyInfo adjInfoToAdd(destinationVertex, arcWeight);
	if (adjList[sourceVertex].length()>0)
	{
		if (adjList[sourceVertex].getAt(adjList[sourceVertex].length()-1)<adjInfoToAdd)
		{
			adjList[sourceVertex].insertAt(adjList[sourceVertex].length(), adjInfoToAdd);
			added = true;
		}
		else
		{
			for (int i = 0; i < adjList[sourceVertex].length(); i++)
			{

				if (adjInfoToAdd<adjList[sourceVertex].getAt(i))
				{
					adjList[sourceVertex].insertAt(i, adjInfoToAdd);
					i = adjList[sourceVertex].length();
					added = true;
				}
			}
		}
		
		
	}
	else
	{
		adjList[sourceVertex].insertAt(0, adjInfoToAdd);
		added = true;
	}
	return added;
}

bool Graph::allVercsKnown(bool*  known ) const
{
	bool allKnown = true;
	int pos = 0;
	while (allKnown&& (pos<nrOfVert))
	{
		allKnown = known[pos++];
	}
	return allKnown;
}

void Graph::removeArcToKnownVert(int source, int neighbour, int weight, List<AdjacencyInfo>* list) const
{
	
	list[source].removeAt(0);
	AdjacencyInfo removeArc(source, weight);
	list[neighbour].removeElement(removeArc);
}



Graph::Graph(GraphType graphType, int nrOfVert)
{
	this->graphType = graphType;
	this->nrOfVert = nrOfVert;
	this->adjList = new List<AdjacencyInfo>[nrOfVert];

}

Graph::~Graph()
{
	delete[]this->adjList;
}

void Graph::reset(int nrOfVert, GraphType graphType)
{
	delete[]this->adjList;
	this->graphType = graphType;
	this->nrOfVert = nrOfVert;
	this->adjList = new List<AdjacencyInfo>[nrOfVert];

}

bool Graph::isDirected() const
{
	bool directed = false;
	if (this->graphType == DIRECTED)
	{
		directed = true;
	}
	return directed;
}

bool Graph::addArc(int sourceVertex, int destinationVertex, int arcWeight)
{
	bool added = false;
	
	if (sourceVertex<nrOfVert && destinationVertex<nrOfVert)
	{
		added=addingArc(sourceVertex, destinationVertex, arcWeight);
		
		if (this->graphType==UNDIRECTED)
		{
			added = addingArc(destinationVertex, sourceVertex, arcWeight);
		}
		
	}

	return added;
}

bool Graph::hasArc(int sourceVertex, int destinationVertex) const
{
	bool hasArc = false;
	if (destinationVertex>0 || destinationVertex<nrOfVert)
	{
		for (int i = 0; i < adjList[sourceVertex].length(); i++)
		{
			if (adjList[sourceVertex].getAt(i).getNeighbourVertex() == destinationVertex)
			{
				hasArc = true;
				i = adjList[sourceVertex].length();
			}
		}
	}
	return hasArc;
}

bool Graph::removeArc(int sourceVertex, int destinationVertex, int arcWeight)
{
	bool removed = false;
	AdjacencyInfo adjInfoToRemove(destinationVertex, arcWeight);

	removed = adjList[sourceVertex].removeElement(adjInfoToRemove);
	if (graphType==UNDIRECTED && removed==true)
	{
		adjInfoToRemove.setNeighbourVertex(sourceVertex);
		removed = adjList[destinationVertex].removeElement(adjInfoToRemove);
	}
	

	return removed;
}

int Graph::getNrOfVertices() const
{
	return nrOfVert;
}

int Graph::outDegreeOfVertex(int theVertex) const
{
	int countVert=0;
	if (adjList[theVertex].length()>0)
	{
		for (int i = 0; i < adjList[theVertex].length(); i++)
		{
			countVert += adjList[theVertex].getAt(i).getArcWeight();
		}
	}
	
	
	return countVert;
}

int Graph::inDegreeOfVertex(int theVertex) const
{
	int countVert = 0;
	if (graphType!=UNDIRECTED)
	{
		for (int i = 0; i < nrOfVert; i++)
		{
			if (i!=theVertex)
			{
				for (int u = 0; u < adjList[i].length(); u++)
				{
					if (adjList[i].getAt(u).getNeighbourVertex() == theVertex)
					{
						countVert += adjList[i].getAt(u).getArcWeight();
						u= adjList[i].length();
					}
				}
			}
		}
	}
	else
	{
		countVert=outDegreeOfVertex(theVertex);
	}
	return countVert;
}

List<int> Graph::getAllVerticesAdjacentTo(int theVertex) const
{
	List<int> neighbours;
	for (int i = 0; i < adjList[theVertex].length(); i++)
	{
		if (!neighbours.findElement(adjList[theVertex].getAt(i).getNeighbourVertex()))
		{
			neighbours.insertAt(neighbours.length(), adjList[theVertex].getAt(i).getNeighbourVertex());
		}
		
	}
	return neighbours;
}

void Graph::minSpanTree(List<AdjacencyInfo> minSpanTree[], int cap, int & totalCost) const
{
	if (graphType==DIRECTED ||cap<nrOfVert)
	{
		throw"Graph is directed or the array cap is to low";
	}

	bool* knownVert=new bool[nrOfVert];
	List<AdjacencyInfo>* helpList=new List<AdjacencyInfo>[nrOfVert];

	for (int i = 0; i < nrOfVert; i++)
	{
		knownVert[i] = false;
		helpList[i] = adjList[i];
	}
	int source = 0;
	minSpanTree[0].insertAt(0, adjList[0].getAt(0));
	int neighbour=helpList[0].getAt(0).getNeighbourVertex();
	totalCost += minSpanTree[0].getAt(0).getArcWeight();
	removeArcToKnownVert(source, neighbour, totalCost, helpList);
	knownVert[0] = true;
	knownVert[neighbour] = true;
	bool allKnown = false;

	while (!allKnown)
	{
		int minArc=999999;
		int minSpot;
		for (int i = 0; i < nrOfVert; i++)
		{
			if (helpList[i].length() > 0)
			{


				if (knownVert[i] == true)
				{
					if (helpList[i].getAt(0).getArcWeight() < minArc)
					{
						if (knownVert[helpList[i].getAt(0).getNeighbourVertex()] != true)
						{
							minArc = helpList[i].getAt(0).getArcWeight();
							neighbour = helpList[i].getAt(0).getNeighbourVertex();
							source = i;
							minSpot = 0;
						}
						else
						{
							for (int u = 0; u < helpList[i].length(); u++)
							{
								int arcRemove = helpList[i].getAt(0).getArcWeight();
								int vertRemove = helpList[i].getAt(0).getNeighbourVertex();
								removeArcToKnownVert(i, vertRemove, arcRemove, helpList);

								if (helpList[i].length() > 0)
								{
									if (helpList[i].getAt(0).getArcWeight() < minArc)
									{
										if (knownVert[helpList[i].getAt(0).getNeighbourVertex()] != true)
										{
											minArc = helpList[i].getAt(0).getArcWeight();
											neighbour = helpList[i].getAt(0).getNeighbourVertex();
											source = i;
											minSpot = u;
											u = helpList[i].length();
										}
									}
									else
									{
										u = helpList[i].length();
									}
								}
								else
								{
									u = helpList[i].length();
								}


							}
						}

					}
				}
			}
		}
		minSpanTree[source].insertAt(minSpanTree[source].length(), helpList[source].getAt(0));
		removeArcToKnownVert(source, neighbour, minArc, helpList);
		knownVert[neighbour] = true;
		totalCost += minArc;
		allKnown = allVercsKnown(knownVert);
	
	}


	delete[] helpList;
	delete[] knownVert;

}

void Graph::printGraph() const
{
	std::stringstream ss;
	ss << nrOfVert << std::endl;
	if (graphType == DIRECTED)
		ss << "D\n";
	else
		ss << "U\n";

	for (int i = 0; i < nrOfVert; i++)
	{
		
		for (int u = 0; u < adjList[i].length(); u++)
		{
			ss << i << " " << adjList[i].getAt(u).getNeighbourVertex() << " " << adjList[i].getAt(u).getArcWeight() << std::endl;
		}
	}

	std::cout << ss.str() << std::endl;
}
