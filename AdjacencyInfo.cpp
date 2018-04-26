#include "AdjacencyInfo.h"


AdjacencyInfo::AdjacencyInfo(int neighbourVertex, int arcWeight)
{
	this->neighbourVertex = neighbourVertex;
	this->arcWeight = arcWeight;
}

AdjacencyInfo::~AdjacencyInfo()
{}

int AdjacencyInfo::getNeighbourVertex() const
{
	return this->neighbourVertex;
}
void AdjacencyInfo::setNeighbourVertex(int neighbourVertex)
{
	if (neighbourVertex < 0)
		throw "No such vertex";
	this->neighbourVertex = neighbourVertex;
}
int AdjacencyInfo::getArcWeight() const
{
	return this->arcWeight;
}
void AdjacencyInfo::setArcWeight(int arcWeight)
{
	this->arcWeight = arcWeight;
}
bool AdjacencyInfo::operator==(const AdjacencyInfo& other) const
{
	return this->neighbourVertex == other.neighbourVertex
		&& this->arcWeight == other.arcWeight;
}
bool AdjacencyInfo::operator!=(const AdjacencyInfo& other) const
{
	return this->neighbourVertex != other.neighbourVertex
		|| this->arcWeight != other.arcWeight;
}

bool AdjacencyInfo::operator<(const AdjacencyInfo & other) const
{
	return this->arcWeight<other.arcWeight;
}


