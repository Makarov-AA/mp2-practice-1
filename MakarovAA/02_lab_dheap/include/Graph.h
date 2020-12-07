#ifndef GRAPH_H
#define GRAPH_H

#include "WeightedEdge.h"
#include "SeparatedSet.h"

class Graph{
private:
	int vertsCount;
	int edgesCount;
	WeightedEdge* edges;

public:
	Graph(int iVertsCount);
	Graph(int iVertsCount, int iEdgesCount, WeightedEdge* iEdges);
	Graph(int iVertsCount, int* adjMatrix);
	Graph(const Graph& copy);
	~Graph();

	int getVertsCount() const;
	int getEdgesCount() const;
	WeightedEdge* getEdges() const;

	bool isConnected() const;
	bool isUndirected() const;
	bool hasLoop() const;

	int connectComponentCount() const;

	int* getAdjMatrix() const;
	void  printAdjMatrix() const;

	static Graph genRandomConnectedGraphNoLoops(int iVertsCount, int minValue, int maxValue);

	bool operator==(const Graph& graph) const;
	bool operator!=(const Graph& graph) const;
	
	const Graph& operator=(const Graph& graph);

	friend std::ostream& operator<<(std::ostream& out, const Graph& graph);
	friend std::istream& operator>>(std::istream& in, Graph& graph);
};

#endif