#ifndef DIJKSTRA_ALGORITHM
#define DIJKSTRA_ALGORITHM

#include "Graph.h"
#include "Distances.h"


static class DijkstraAlgorithm
{
public:
	static Distances dijkstraAlgorithm(const Graph& graph, int startVertex);
};
#endif
