#ifndef DIJKSTRA_ALGORITHM
#define DIJKSTRA_ALGORITHM

#include "Graph.h"


static class DijkstraAlgorithm
{
public:
	static Distances dijkstraAlgorithm(const Graph& _graph, const int _startVertex);
};
#endif
