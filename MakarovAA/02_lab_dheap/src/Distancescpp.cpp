#include "Distances.h"

Distances::Distances(int iStartVertex, int iVertsCount, double* iDist, int* iUp)
{
	startVertex = iStartVertex;
	vertsCount = iVertsCount;
	dist = new double[vertsCount];
	up = new int[vertsCount];

	for (int i = 0; i < vertsCount; i++)
		dist[i] = iDist[i];

	for (int i = 0; i < vertsCount; i++)
		up[i] = iUp[i];
}

Distances::Distances(const Distances& distances)
{
	startVertex = distances.startVertex;
	vertsCount = distances.vertsCount;
	dist = new double[vertsCount];
	up = new int[vertsCount];

	for (int i = 0; i < vertsCount; i++)
		dist[i] = distances.dist[i];

	for (int i = 0; i < vertsCount; i++)
		up[i] = distances.up[i];
}

Distances::~Distances()
{
	if (dist) delete[] dist;
	if (up) delete[] up;
}

bool Distances::operator==(const Distances& distances) const
{
	if (startVertex != distances.startVertex)
		return false;
	if (vertsCount != distances.vertsCount)
		return false;

	for (int i = 0; i < vertsCount; i++)
		if (dist[i] != distances.dist[i])
			return false;

	for (int i = 0; i < vertsCount; i++)
		if (up[i] != distances.up[i])
			return false;

	return true;
}

bool Distances::operator!=(const Distances& distances) const
{
	return !(*this != distances);
}

const Distances& Distances::operator=(const Distances& distances)
{
	if (*this == distances)
		return *this;

	startVertex = distances.startVertex;
	vertsCount = distances.vertsCount;

	if (dist) delete[] dist;
	if (up) delete[] up;

	dist = new double[vertsCount];
	for (int i = 0; i < vertsCount; i++)
		dist[i] = distances.dist[i];

	up = new int[vertsCount];
	for (int i = 0; i < vertsCount; i++)
		up[i] = distances.up[i];

	return *this;
}

void Distances::printPaths() const
{
	int* paths = new int[vertsCount * vertsCount];
	for (int i = 0; i < vertsCount * vertsCount; i++)
		paths[i] = -1;

	for (int i = 0; i < vertsCount; i++)
	{
		if (i == startVertex) continue;
		int idx = i * vertsCount + (vertsCount - 1);
		for (int vertex = i; vertex != startVertex; vertex = up[vertex])
			paths[idx--] = vertex;
		paths[idx] = startVertex;
	}

	for (int i = 0; i < verticesCount; i++)
	{
		if (i == startVertex) continue;
		std::cout << "distance(" << startVertex << ", " << i << ") = " << dist[i] << " || ";
		std::cout << "{" << startVertex << "}-->";
		for (int j = 0; j < verticesCount - 1; j++)
		{
			int vertex = paths[i * verticesCount + j];
			if ((vertex >= 0) && (vertex != startVertex))
				std::cout << "[" << vertex << "]-->";
		}
		std::cout << "{" << i << "}" << std::endl;
	}

	delete[] paths;
}

std::ostream& operator<<(std::ostream& out, const TDistances& _distances)
{
	out << "Start vertex: " << _distances.startVertex << std::endl;
	out << "Count of vertices: " << _distances.verticesCount << std::endl;

	out << "Dist: [ ";
	for (int i = 0; i < _distances.verticesCount; i++)
		out << _distances.dist[i] << " ";
	out << "]" << std::endl;

	out << "Up: [ ";
	for (int i = 0; i < _distances.verticesCount; i++)
		out << _distances.up[i] << " ";
	out << "]" << std::endl << std::endl;

	_distances.printPaths();

	return out;
}
