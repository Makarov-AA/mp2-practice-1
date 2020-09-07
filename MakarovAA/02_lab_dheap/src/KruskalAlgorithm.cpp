#include "KruskalAlgorithm.h"
#include "MyException.h"
#include "SeparatedSet.h"
#include "TDheap.h"

Graph KruskalAlgorithm::kruskalAlgorithm(const Graph& graph) {
	const int baseD = 2;

	int vertsCount = graph.getVertsCount();
	int edgesCount = graph.getEdgesCount();

	if (vertsCount < 1)
		throw MyException("Incorrect vertices count");

	if (!graph.isConnected())
		throw MyException("Graph is disconnected");

	if (graph.hasLoop())
		throw MyException("Graph has loops");

	SeparatedSet verts(vertsCount);
	for (int i = 0; i < vertsCount; i++)
		verts.createSingleton(i);

	WeightedEdge* resultEdges = new WeightedEdge[vertsCount - 1];
	int currEdgesCount = 0;

	TDHeap<WeightedEdge> edges(baseD, edgesCount, edgesCount, graph.getEdges());

	while (currEdgesCount != vertsCount - 1)
	{
		WeightedEdge minEdge = edges.getMinElm();
		edges.removeMinElm();
		if (verts.getSetName(minEdge.getStartVertex())
			!= verts.getSetName(minEdge.getEndVertex()))
		{
			verts.unite(verts.getSetName(minEdge.getStartVertex()),
				verts.getSetName(minEdge.getEndVertex()));
			resultEdges[currEdgesCount++] = minEdge;
		}
	}

	Graph resultTree(vertsCount, vertsCount - 1, resultEdges);

	delete[] resultEdges;
	return resultTree;
}