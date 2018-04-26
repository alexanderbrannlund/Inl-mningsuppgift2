#pragma once
#pragma once

class AdjacencyInfo
{
private:
	int neighbourVertex;
	int arcWeight;
public:
	AdjacencyInfo(int neighbourVertex = -1, int arcWeight = 0);
	virtual ~AdjacencyInfo();
	int getNeighbourVertex() const;
	void setNeighbourVertex(int neighbourVertex);
	int getArcWeight() const;
	void setArcWeight(int arcWeight);
	bool operator==(const AdjacencyInfo& other) const;
	bool operator!=(const AdjacencyInfo& other) const;
	bool operator <(const AdjacencyInfo& other) const;

};
