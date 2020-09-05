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

	bool isConnected()    const;
	bool isUndirected()   const;
	bool hasLoop()        const;

	int connectComponentCount() const;

	int* getAdjMatrix() const;
	void  printAdjacencyMatrix() const;

	static Graph generateRandomDigraph(int _verticesCount, int _min, int _max);
	static Graph generateRandomUndirectedGraph(int _verticesCount, int _min, int _max);
	static Graph generateRandomConnectedGraph(int _verticesCount, int _min, int _max);
	static Graph genRandomConnectedGraphNoLoops(int iVertsCount, int minValue, int maxValue);

	bool operator==(const TGraph& _graph) const;
	bool operator!=(const TGraph& _graph) const;

	const TGraph& operator=(const TGraph& _graph);

	friend std::ostream& operator<<(std::ostream& out, const TGraph& _graph);
	friend std::istream& operator>>(std::istream& in, TGraph& _graph);
};

#endif