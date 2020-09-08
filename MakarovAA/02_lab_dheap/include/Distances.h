#ifndef DISTANCES
#define DISTANCES

#include <iostream>

class Distances
{
private:
	int startVertex;
	int vertsCount;
	double* dist;
	int* parentList;

public:
	Distances(int iStartVertex, int iVertsCount, int* iDist, int* iLongestPath);
	Distances(const Distances& distances);
	~Distances();

	bool operator==(const Distances& distances) const;
	bool operator!=(const Distances& distances) const;

	const Distances& operator=(const Distances& _distances);

	friend std::ostream& operator<<(std::ostream& out, const Distances& distances);

	void printPaths() const;
};

#endif
