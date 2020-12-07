#ifndef WEIGHTED_EDGE_H
#define WEIGHTED_EDGE_H

#include <iostream>

class WeightedEdge {
private:
	int startVertex;
	int endVertex;
	int weight;
public:
	WeightedEdge();
	WeightedEdge(int iStartVertex, int iEndVertex, int iWeight);
	WeightedEdge(const WeightedEdge& copy);
	~WeightedEdge() = default;

	bool operator > (const WeightedEdge& edge) const;
	bool operator < (const WeightedEdge& edge) const;
	bool operator >= (const WeightedEdge& edge) const;
	bool operator <=(const WeightedEdge& edge) const;
	bool operator == (const WeightedEdge& edge) const;
	bool operator != (const WeightedEdge& edge) const;

	const WeightedEdge& operator=(const WeightedEdge& edge);

	int getStartVertex() const;
	int getEndVertex() const;

	void setStartVertex(int iStartVertex);
	void setEndVertex(int iEndVertex);

	int getWeight() const;
	void setWeight(int iWeight);

	bool isIncidental(int vertex) const;
	bool isAdjacent(WeightedEdge edge) const;

	friend std::ostream& operator<<(std::ostream& out, const WeightedEdge& edge);
	friend std::istream& operator>>(std::istream& in, WeightedEdge& edge);

};

#endif
