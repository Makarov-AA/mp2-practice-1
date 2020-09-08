#ifndef LABEL
#define LABEL

#include <iostream>

class Label
{
private:
	int vertex;
	int distance;

public:
	Label();
	Label(int iVertex, int iDistance);
	~Label() {};

	int getVertex() const;
	int getDistance() const;

	void setVertex(int iVertex);
	void setDistance(int iDistance);

	bool operator==(const Label& label) const;
	bool operator!=(const Label& label) const;

	bool operator> (const Label& label) const;
	bool operator< (const Label& label) const;
	bool operator>=(const Label& label) const;
	bool operator<=(const Label& label) const;

	const Label& operator=(const Label& label);

	friend std::ostream& operator<<(std::ostream& out, const Label& label);
	friend std::istream& operator>>(std::istream& in, Label& label);
};

#endif
