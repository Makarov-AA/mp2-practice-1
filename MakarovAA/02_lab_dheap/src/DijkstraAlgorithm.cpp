#define D 2

#include "DijkstraAlgorithm.h"
#include "MyException.h"
#include "SeparatedSet.h"
#include "Label.h"
#include "TDheap.h"

Distances DijkstraAlgorithm::dijkstraAlgorithm(const Graph& graph, int startVertex){

	WeightedEdge* edges = graph.getEdges();
	int edgesCount = graph.getEdgesCount();
	int vertsCount = graph.getVertsCount();

	if (vertsCount < 0)
		throw MyException("Graph doesn't have any vertices");

	if ((startVertex < 0) || (startVertex > vertsCount))
		throw MyException("Incorrect start vertex");

	if (!graph.isConnected())
		throw MyException("Disconnected graph");

	if (graph.hasLoop())
		throw MyException("Graph has loops");

	for (int i = 0; i < edgesCount; i++)
		if (edges[i].getWeight() < 0)
			throw MyException("Weight of edges has to be non-negative for Dijkstra algorithm");

	Label* labels = new Label[vertsCount];
	int* dist = new int[vertsCount];
	int* parentList = new int[vertsCount];

	for (int i = 0; i < vertsCount; i++){
		labels[i].setDistance(INT_MAX);
		labels[i].setVertex(i);
		parentList[i] = startVertex;
	}
	labels[startVertex].setDistance(0);

	TDHeap<Label> labelsQueue(D, vertsCount, vertsCount, labels);
	delete[] labels;
	labels = labelsQueue.getDataPointer();

	while (labelsQueue.getCurrSize() != 0){
		Label label = labelsQueue.getMinElm();
		Label* adjVerts = new Label[vertsCount - 1];
		int adjVertsCount = 0;

		for (int i = 0; i < edgesCount; i++)
			if (edges[i].isIncidental(label.getVertex()))
				adjVerts[adjVertsCount++] = Label((edges[i].getStartVertex() == label.getVertex()) ?
					edges[i].getEndVertex() : edges[i].getStartVertex(), edges[i].getWeight());

		for (int i = 0; i < adjVertsCount; i++){
			int idx = 0;
			while ((idx < vertsCount) &&
				(adjVerts[i].getVertex() != labels[idx].getVertex()))
				idx++;

			if (label.getDistance() + adjVerts[i].getDistance() < labels[idx].getDistance()){
				labels[idx].setDistance(label.getDistance() + adjVerts[i].getDistance());
				parentList[adjVerts[i].getVertex()] = label.getVertex();
			}
		}
		dist[label.getVertex()] = label.getDistance();

		labelsQueue.removeMinElm();

		delete[] adjVerts;
	}

	Distances result(startVertex, vertsCount, dist, parentList);

	delete[] dist;
	delete[] parentList;
	delete[] labels;

	return result;
};