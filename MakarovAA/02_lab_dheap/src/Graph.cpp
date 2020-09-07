#include "Graph.h"
#include "MyException.h"

Graph::Graph(int iVertsCount){
	if (iVertsCount < 0)
		throw MyException("Incorrect vertexes count");
	vertsCount = iVertsCount;
	edgesCount = 0;
	edges = nullptr;
}

Graph::Graph(int iVertsCount, int iEdgesCount, WeightedEdge* iEdges){
	if (iVertsCount < 0)
		throw MyException("Incorrect vertexes count");
	if ((iEdgesCount < 0) || (iEdgesCount > iVertsCount * iVertsCount))
		throw MyException("Incorrect edges count");

	vertsCount = iVertsCount;
	edgesCount = iEdgesCount;
	edges = new WeightedEdge[edgesCount];

	for (int i = 0; i < edgesCount; i++)
	{
		if ((edges[i].getStartVertex() >= vertsCount)
			|| (edges[i].getEndVertex() >= vertsCount))
		{
			delete[] edges;
			throw MyException("Incorrect edges for graph");
		}
		edges[i] = iEdges[i];
	}
}

Graph::Graph(int iVertsCount, int* adjMatrix){
	if (iVertsCount < 0)
		throw MyException("Incorrect vertexes count");

	vertsCount = iVertsCount;
	edgesCount = 0;

	for (int i = 0; i < iVertsCount * iVertsCount; i++)
		if (adjMatrix[i] != 0)
			edgesCount++;

	edges = new WeightedEdge[edgesCount];

	for (int i = 0, currIdx = 0; i < vertsCount * vertsCount; i++)
	{
		if (adjMatrix[i] != 0)
		{
			edges[currIdx].setStartVertex(i % vertsCount);
			edges[currIdx].setEndVertex(i / vertsCount);
			edges[currIdx++].setWeight(adjMatrix[i]);
		}
	}
}

Graph::Graph(const Graph& copy){
	vertsCount = copy.vertsCount;
	edgesCount = copy.edgesCount;
	edges = new WeightedEdge[edgesCount];
	for (int j = 0; j < edgesCount; j++)
		edges[j] = copy.edges[j];
}

Graph::~Graph(){
	delete[] edges;
}

int Graph::getVertsCount() const{
	return vertsCount;
}

int Graph::getEdgesCount() const{
	return edgesCount;
}

WeightedEdge* Graph::getEdges() const{
	return edges;
}

bool Graph::isConnected() const{
	if (connectComponentCount() <= 0)
		throw MyException("There is no vertices in graph");
	if (connectComponentCount() == 1)
		return true;
	return false;
}

bool Graph::isUndirected() const{
	for (int i = 0; i < edgesCount - 1; i++)
		for (int j = i + 1; j < edgesCount; j++)
		{
			if ((edges[i].getEndVertex() == edges[j].getStartVertex())
				&& (edges[i].getStartVertex() == edges[j].getEndVertex()))
				return false;
		}
	return true;
}

bool Graph::hasLoop() const{
	for (int i = 0; i < edgesCount; i++)
		if (edges[i].getStartVertex() == edges[i].getEndVertex())
			return true;
	return false;
}

int Graph::connectComponentCount() const{
	if (vertsCount == 0) return 0;
	if (edgesCount == 0) return vertsCount;

	int result = vertsCount;
	SeparatedSet components(vertsCount);
	for (int i = 0; i < vertsCount; i++)
		components.createSingleton(i);

	for (int i = 0; i < edgesCount; i++)
	{
		if (components.getSetName(edges[i].getStartVertex())
			!= components.getSetName(edges[i].getEndVertex()))
		{
			components.unite(components.getSetName(edges[i].getStartVertex()),
				components.getSetName(edges[i].getEndVertex()));
			result--;
		}
	}

	return result;
}

int* Graph::getAdjMatrix() const{
	int* adjMatrix = new int[vertsCount * vertsCount];
	for (int k = 0; k < vertsCount * vertsCount; k++)
		adjMatrix[k] = 0;

	bool isUndirectedGraph = this->isUndirected();

	for (int i = 0; i < edgesCount; i++)
	{
		WeightedEdge edge = edges[i];
		int startVertex = edge.getStartVertex();
		int endVertex = edge.getEndVertex();
		adjMatrix[startVertex * vertsCount + endVertex] = edge.getWeight();
		if (isUndirectedGraph)
			adjMatrix[endVertex * vertsCount + startVertex] = edge.getWeight();
	}

	return adjMatrix;
}

void Graph::printAdjMatrix() const{
	int* adjacencyMatrix = getAdjMatrix();

	for (int i = 0; i < vertsCount; i++)
	{
		for (int j = 0; j < vertsCount; j++)
			std::cout << adjacencyMatrix[i * vertsCount + j] << " ";
		std::cout << std::endl;
	}

	delete[] adjacencyMatrix;
}

Graph Graph::genRandomConnectedGraphNoLoops(int iVertsCount, int minValue, int maxValue){
	if (iVertsCount < 0)
		throw MyException("Incorrect vertexes count");

	if (minValue > maxValue)
		throw MyException("Maximal value cannot be lesser than minimal");

	int* adjMatrix = new int[iVertsCount * iVertsCount];
	for (int i = 0; i < iVertsCount * iVertsCount; i++)
		adjMatrix[i] = 0;

	int minEdgesCount = iVertsCount - 1;
	int maxEdgesCount = iVertsCount * (iVertsCount - 1) / 2;
	int edgesCount = (int)((double)(maxEdgesCount - minEdgesCount) / 
		(double)RAND_MAX * (double)rand()) + minEdgesCount;

	int* path = new int[iVertsCount];
	for (int i = 0; i < iVertsCount; i++)
		path[i] = i;
	for (int i = iVertsCount - 1; i >= 0; i--){
		int j = i / (double)RAND_MAX * rand();
		int tmp = path[i];
		path[i] = path[j];
		path[j] = tmp;
	}

	for (int i = 0; i < iVertsCount - 1; i++){
		int idx;
		if (path[i] <= path[i + 1])
			idx = path[i] * iVertsCount + path[i + 1];
		else
			idx = path[i + 1] * iVertsCount + path[i];
		adjMatrix[idx] = (maxValue - minValue + 1) / (double)RAND_MAX * rand() + minValue;
	}
	delete[] path;

	int* idxs = new int[maxEdgesCount - minEdgesCount];
	for (int i = 0, j = 0; i < iVertsCount * iVertsCount; i++)
		if ((i / iVertsCount < i % iVertsCount) && (adjMatrix[i] == 0))
			idxs[j++] = i;

	for (int i = maxEdgesCount - minEdgesCount - 1; i >= maxEdgesCount - edgesCount; i--)
	{
		int j = i / (double)RAND_MAX * rand();
		int tmp = idxs[i];
		idxs[i] = idxs[j];
		idxs[j] = tmp;

		adjMatrix[idxs[i]] = (maxValue - minValue + 1) / (double)RAND_MAX * rand() + minValue;
	}
	delete[] idxs;

	Graph resultGraph(iVertsCount, adjMatrix);
	delete[] adjMatrix;

	return resultGraph;
}

bool Graph::operator==(const Graph& graph) const{
	if ((vertsCount != graph.vertsCount)
		|| (edgesCount != graph.edgesCount))
		return false;

	for (int i = 0; i < edgesCount; i++)
		if (edges[i] != graph.edges[i])
			return false;

	return true;
}

bool Graph::operator!=(const Graph& graph) const{
	return !(*this == graph);
}

const Graph& Graph::operator=(const Graph& graph){
	if (*this == graph)
		return *this;

	vertsCount = graph.vertsCount;
	edgesCount = graph.edgesCount;

	if (!edges)
		delete[] edges;
	edges = new WeightedEdge[edgesCount];

	for (int i = 0; i < edgesCount; i++)
		edges[i] = graph.edges[i];

	return *this;
}

std::ostream& operator<<(std::ostream& out, const Graph& graph)
{
	out << "Vertices: [ ";
	for (int i = 0; i < graph.vertsCount; i++)
		out << i << ", ";
	out << "]" << std::endl;
	out << "Edges: [ ";
	for (int i = 0; i < graph.edgesCount; i++)
		out << graph.edges[i] << " ";
	out << "]" << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Graph& graph)
{
	int vertsCount;
	int edgesCount;
	WeightedEdge* edges;

	std::cout << std::endl;
	std::cout << "Enter count of vertices: ";
	in >> vertsCount;
	if (vertsCount <= 0)
		throw MyException("Incorrect vertexes count");
	std::cout << "Enter count of edges: ";
	in >> edgesCount;
	if (edgesCount <= 0)
		throw MyException("Incorrect edges count");

	edges = new WeightedEdge[edgesCount];
	std::cout << std::endl;

	for (int i = 0; i < edgesCount; i++)
	{
		std::cout << "Input edge ¹ " << i << std::endl;
		in >> edges[i];
		std::cout << std::endl;
	}

	graph = Graph(vertsCount, edgesCount, edges);
	delete[] edges;
	return in;
};