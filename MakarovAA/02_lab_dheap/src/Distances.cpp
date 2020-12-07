#include "Distances.h"

Distances::Distances(int iStartVertex, int iVertsCount, int* iDist, int* iParentList)
{
	startVertex = iStartVertex;
	vertsCount = iVertsCount;
	dist = new double[vertsCount];
	parentList = new int[vertsCount];

	for (int i = 0; i < vertsCount; i++)
		dist[i] = iDist[i];

	for (int i = 0; i < vertsCount; i++)
		parentList[i] = iParentList[i];
}

Distances::Distances(const Distances& distances)
{
	startVertex = distances.startVertex;
	vertsCount = distances.vertsCount;
	dist = new double[vertsCount];
	parentList = new int[vertsCount];

	for (int i = 0; i < vertsCount; i++)
		dist[i] = distances.dist[i];

	for (int i = 0; i < vertsCount; i++)
		parentList[i] = distances.parentList[i];
}

Distances::~Distances()
{
	if (dist) delete[] dist;
	if (parentList) delete[] parentList;
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
		if (parentList[i] != distances.parentList[i])
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
	if (parentList) delete[] parentList;

	dist = new double[vertsCount];
	for (int i = 0; i < vertsCount; i++)
		dist[i] = distances.dist[i];

	parentList = new int[vertsCount];
	for (int i = 0; i < vertsCount; i++)
		parentList[i] = distances.parentList[i];

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
		for (int vertex = i; vertex != startVertex; vertex = parentList[vertex])
			paths[idx--] = vertex;
		paths[idx] = startVertex;
	}

	for (int i = 0; i < vertsCount; i++)
	{
		if (i == startVertex) continue;
		std::cout << "distance(" << startVertex << ", " << i << ") = " << dist[i] << std::endl;
		std::cout << "Path: " << "{" << startVertex << "}-->";
		for (int j = 0; j < vertsCount - 1; j++)
		{
			int vertex = paths[i * vertsCount + j];
			if ((vertex >= 0) && (vertex != startVertex))
				std::cout << "[" << vertex << "]-->";
		}
		std::cout << "{" << i << "}" << std::endl;
	}

	delete[] paths;
}

std::ostream& operator<<(std::ostream& out, const Distances& distances)
{
	out << "Start vertex: " << distances.startVertex << std::endl;
	out << "Count of vertices: " << distances.vertsCount << std::endl;

	out << "Distances: [ ";
	for (int i = 0; i < distances.vertsCount; i++)
		out << distances.dist[i] << " ";
	out << "]" << std::endl;

	out << "ParentList: [ ";
	for (int i = 0; i < distances.vertsCount; i++)
		out << distances.parentList[i] << " ";
	out << "]" << std::endl << std::endl;

	distances.printPaths();

	return out;
}
