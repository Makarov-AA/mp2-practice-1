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

void Graph::printAdjacencyMatrix() const{
	int* adjacencyMatrix = getAdjMatrix();

	for (int i = 0; i < vertsCount; i++)
	{
		for (int j = 0; j < vertsCount; j++)
			std::cout << adjacencyMatrix[i * vertsCount + j] << " ";
		std::cout << std::endl;
	}

	delete[] adjacencyMatrix;
}

Graph Graph::generateRandomDigraph(int _verticesCount, int _min, int _max){
	if (_verticesCount < 0)
		throw ExceptionIncorrectCountOfVertices(__LINE__, __FILE__);

	if (_min > _max)
		throw ExceptionIncorrectValueBoundaries(__LINE__, __FILE__);

	double* adjacencyMatrix = new double[_verticesCount * _verticesCount];

	for (int i = 0; i < _verticesCount * _verticesCount; i++)
	{
		if (rand() / (double)RAND_MAX < .5)
			adjacencyMatrix[i] = 0;
		else
			adjacencyMatrix[i] = (_max - _min + 1) / (double)RAND_MAX * rand() + _min;
	}

	TGraph resultGraph(_verticesCount, adjacencyMatrix);
	delete[] adjacencyMatrix;

	return resultGraph;
}

TGraph TGraph::generateRandomUndirectedGraph(int _verticesCount, int _min, int _max){
	if (_verticesCount < 0)
		throw ExceptionIncorrectCountOfVertices(__LINE__, __FILE__);

	if (_min > _max)
		throw ExceptionIncorrectValueBoundaries(__LINE__, __FILE__);

	double* adjacencyMatrix = new double[_verticesCount * _verticesCount];

	for (int i = 0; i < _verticesCount; i++)
		for (int j = 0; j < _verticesCount; j++)
			adjacencyMatrix[i * _verticesCount + j]
			= (j < i) ? 0 : (_max - _min + 1) / (double)RAND_MAX * rand() + _min;

	TGraph resultGraph(_verticesCount, adjacencyMatrix);
	delete[] adjacencyMatrix;

	return resultGraph;
}

TGraph TGraph::generateRandomConnectedGraph(int _verticesCount, int _min, int _max){
	if (_verticesCount < 0)
		throw ExceptionIncorrectCountOfVertices(__LINE__, __FILE__);

	if (_min > _max)
		throw ExceptionIncorrectValueBoundaries(__LINE__, __FILE__);

	double* adjacencyMatrix = new double[_verticesCount * _verticesCount];
	for (int i = 0; i < _verticesCount * _verticesCount; i++)
		adjacencyMatrix[i] = 0;

	int _minEdgesCount = _verticesCount - 1;
	int _maxEdgesCount = _verticesCount * (_verticesCount + 1) / 2;
	int edgesCount = (_maxEdgesCount - _minEdgesCount) / (double)RAND_MAX * rand() + _minEdgesCount;

	int* path = new int[_verticesCount];
	for (int i = 0; i < _verticesCount; i++)
		path[i] = i;
	for (int i = _verticesCount - 1; i >= 0; i--)
	{
		int j = i / (double)RAND_MAX * rand();
		int tmp = path[i];
		path[i] = path[j];
		path[j] = tmp;
	}

	for (int j = 0; j < _verticesCount - 1; j++)
	{
		int idx;
		if (path[j] <= path[j + 1])
			idx = path[j] * _verticesCount + path[j + 1];
		else
			idx = path[j + 1] * _verticesCount + path[j];
		adjacencyMatrix[idx] = (_max - _min + 1) / (double)RAND_MAX * rand() + _min;
	}
	delete[] path;

	int* indexes = new int[_maxEdgesCount - _minEdgesCount];
	for (int i = 0, j = 0; i < _verticesCount * _verticesCount; i++)
	{
		if ((i / _verticesCount <= i % _verticesCount) && (adjacencyMatrix[i] == 0))
			indexes[j++] = i;
	}

	for (int i = _maxEdgesCount - _minEdgesCount - 1; i >= _maxEdgesCount - edgesCount; i--)
	{
		int j = i / (double)RAND_MAX * rand();
		int tmp = indexes[i];
		indexes[i] = indexes[j];
		indexes[j] = tmp;

		adjacencyMatrix[indexes[i]] = (_max - _min + 1) / (double)RAND_MAX * rand() + _min;
	}
	delete[] indexes;

	TGraph resultGraph(_verticesCount, adjacencyMatrix);
	delete[] adjacencyMatrix;

	return resultGraph;
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

	for (int i = _maxEdgesCount - _minEdgesCount - 1; i >= _maxEdgesCount - edgesCount; i--)
	{
		int j = i / (double)RAND_MAX * rand();
		int tmp = indexes[i];
		indexes[i] = indexes[j];
		indexes[j] = tmp;

		adjacencyMatrix[indexes[i]] = (_max - _min + 1) / (double)RAND_MAX * rand() + _min;
	}
	delete[] indexes;

	TGraph resultGraph(_verticesCount, adjacencyMatrix);
	delete[] adjacencyMatrix;

	return resultGraph;
}

bool TGraph::operator==(const TGraph& _graph) const
{
	if ((verticesCount != _graph.verticesCount)
		|| (edgesCount != _graph.edgesCount))
		return false;

	for (int i = 0; i < edgesCount; i++)
		if (edges[i] != _graph.edges[i])
			return false;

	return true;
}

bool TGraph::operator!=(const TGraph& _graph) const
{
	return !(*this == _graph);
	/*
	if ((verticesCount != _graph.verticesCount)
		|| (edgesCount != _graph.edgesCount))
	  return true;

	for (int i = 0; i < edgesCount; i++)
	  if (edges[i] != _graph.edges[i])
		return true;

	return false;
	*/
}

const TGraph& TGraph::operator=(const TGraph& _graph)
{
	if (*this == _graph)
		return *this;

	verticesCount = _graph.verticesCount;
	edgesCount = _graph.edgesCount;

	if (!edges)
		delete[] edges;
	edges = new TWeightedEdge[edgesCount];

	for (int i = 0; i < edgesCount; i++)
		edges[i] = _graph.edges[i];

	return *this;
}

std::ostream& operator<<(std::ostream& out, const TGraph& _graph)
{
	out << "Vertices: [ ";
	for (int i = 0; i < _graph.verticesCount; i++)
		out << i << " ";
	out << "]" << std::endl;
	out << "Edges: [ ";
	for (int i = 0; i < _graph.edgesCount; i++)
		out << _graph.edges[i] << " ";
	out << "]" << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, TGraph& _graph)
{
	int _verticesCount;
	int _edgesCount;
	TWeightedEdge* _edges;

	std::cout << std::endl;
	std::cout << "Enter count of vertices: ";
	in >> _verticesCount;
	std::cout << "Enter count of edges: ";
	in >> _edgesCount;

	_edges = new TWeightedEdge[_edgesCount];
	std::cout << std::endl;

	for (int i = 0; i < _edgesCount; i++)
	{
		std::cout << " -----| Edge #" << i << " |----- " << std::endl;
		in >> _edges[i];
		std::cout << std::endl;
	}

	_graph = TGraph(_verticesCount, _edgesCount, _edges);
	delete[] _edges;
	return in;
};