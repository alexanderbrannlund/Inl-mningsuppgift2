#include"Graph.h"
#include<iostream>
#include<string>
#include<fstream>
#include <sstream>

bool readFromFile(std::string filename, Graph *graph);
void testHasArc(Graph *graph);
void testIsDirected(Graph* graph);
void testRemoveArc(Graph* graph);
void testGetNrOfVertices(Graph* graph);
void testOutDegreeOfVertex(Graph* graph);
void testOutDegreeOfVertex();
void testGetAllVerticesAdjacentTo(Graph* graph);
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool test = false;

	Graph* graph= new Graph();
	test = readFromFile("Graph.txt", graph);
	if (test)
	{
		graph->printGraph();
		std::cout << std::endl << std::endl;
		std::cout << "Testing all functions...."<<std::endl;
		"Function addArc is working! \n";
	}

	std::cout << std::endl << std::endl;
	std::cin.get();
	testHasArc(graph);
	std::cout << std::endl;
	std::cin.get();
	testIsDirected(graph);
	std::cin.get();
	testRemoveArc(graph);
	graph->printGraph();
	std::cin.get();
	testGetNrOfVertices(graph);
	std::cin.get();
	testOutDegreeOfVertex(graph);
	std::cin.get();
	testOutDegreeOfVertex();
	std::cin.get();
	testGetAllVerticesAdjacentTo(graph);

	std::cin.get();
	std::cout << std::endl << std::endl;
	test = readFromFile("Graph.txt", graph); //den första oriktade grafen
	std::cout << "Presenting minimum spanning tree...." << std::endl;
	const int cap = graph->getNrOfVertices();

	List<AdjacencyInfo>* mst= new List<AdjacencyInfo>[cap];
	int totalCost = 0;

	std::stringstream ss;

	graph->minSpanTree(mst, cap, totalCost);

	for (int i = 0; i < cap; i++)
	{

		for (int u = 0; u < mst[i].length(); u++)
		{
			ss << i << " " << mst[i].getAt(u).getNeighbourVertex() << " " << mst[i].getAt(u).getArcWeight() << std::endl;
		}
	}

	std::cout << ss.str() << std::endl;

	std::cout << "Total cost: " << std::to_string(totalCost) << std::endl;


	
	

	std::cin.get();
	delete[] mst;
	delete[] graph;
	return 0;
}

bool readFromFile(std::string filename, Graph * graph)
{
	bool done = false;
	
	std::ifstream fileIn(filename);
	if (fileIn.is_open())
	{
		int nrOfNodes;
		std::string graftype;
		int source;
		int neighbours;
		int weight;
		fileIn >> nrOfNodes;
		fileIn.ignore();
		getline(fileIn,graftype);

		if (graftype[0] == 'U')
		{
			graph->reset(nrOfNodes, UNDIRECTED);
		}
		else
		{
			graph->reset(nrOfNodes, DIRECTED);
		}

		while (fileIn>>source)
		{
			fileIn.ignore();
			fileIn >> neighbours;
			fileIn.ignore();
			fileIn >> weight;
			fileIn.ignore();
			graph->addArc(source, neighbours, weight);
		}
		done = true;
	}

	return done;
}

void testHasArc(Graph * graph)
{
	bool test = false;
	test = graph->hasArc(0, 2);
	if (test)
	{
		test = graph->hasArc(6, 0);
		if (!test)
		{
			std::cout << "Function hasArc is working! \n";
		}
		else
		{
			std::cout << "Function hasArc is not working for not excisting arcs! \n";
		}
	}
	else
	{
		std::cout << "Function hasArc Error! \n";
	}
}

void testIsDirected(Graph * graph)
{
	bool test = false;
	test = graph->isDirected();
	if (!test)
	{
		std::cout << "Function isDirected is working! \n";
	}

	else
	{
		std::cout << "Function isDirected Error! \n";
	}
}

void testRemoveArc(Graph * graph)
{
	bool test = false;
	test = graph->removeArc(0, 2, 40);

	if (test)
	{
		std::cout << "Function removeArc is working! \n";
	}

	else
	{
		std::cout << "Function removeArc Error! \n";
	}
}

void testGetNrOfVertices(Graph * graph)
{
	int test = graph->getNrOfVertices();

	if (test==7)
	{
		std::cout << "Function getNrOfVertices is working! \n";
	}

	else
	{
		std::cout << "Function getNrOfVertices Error! \n";
	}
	

}

void testOutDegreeOfVertex(Graph * graph)
{
	int test = graph->outDegreeOfVertex(0);

	if (test == 30)
	{
		std::cout << "Function OutDegreeOfVertex is working! \n";
	}

	else
	{
		std::cout << "Function OutDegreeOfVertex Error! \n";
	}

}

void testOutDegreeOfVertex()
{
	Graph graph(DIRECTED,4);
	graph.addArc(0, 2, 40);
	graph.addArc(3, 0, 10);
	graph.addArc(1, 2, 50);
	graph.addArc(3, 1, 80);
	graph.addArc(2, 3, 20);

	int test=graph.inDegreeOfVertex(2);

	if (test == 90)
	{
		std::cout << "Function inDegreeOfVertex is working! \n";
	}

	else
	{
		std::cout << "Function inDegreeOfVertex Error! \n";
	}
	




}

void testGetAllVerticesAdjacentTo(Graph * graph)
{
	List<int> intList = graph->getAllVerticesAdjacentTo(6);

	for (int i = 0; i < intList.length(); i++)
	{
		std::cout << std::to_string(intList.getAt(i)) << std::endl;
	}
}
