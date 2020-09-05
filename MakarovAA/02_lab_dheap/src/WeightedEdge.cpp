#include "WeightedEdge.h"
#include "MyException.h"

WeightedEdge::WeightedEdge() {
	startVertex = 0;
	endVertex = 0;
	weight = 0;
}

WeightedEdge::WeightedEdge(int iStartVertex, int iEndVertex, int iWeight) {
	startVertex = iStartVertex;
	endVertex = iEndVertex;
	weight = iWeight;
}

WeightedEdge::WeightedEdge(const WeightedEdge& copy) {
	startVertex = copy.startVertex;
	endVertex = copy.endVertex;
	weight = copy.weight;
}

bool WeightedEdge::operator > (const WeightedEdge& edge) const {
	return weight > edge.weight;
}

bool WeightedEdge::operator < (const WeightedEdge& edge) const {
	return weight < edge.weight;
}

bool WeightedEdge::operator >= (const WeightedEdge& edge) const {
	return weight >= edge.weight;
}

bool WeightedEdge::operator <= (const WeightedEdge& edge) const {
	return weight < edge.weight;
}

bool WeightedEdge::operator == (const WeightedEdge& edge) const {
	return (startVertex == edge.startVertex && endVertex == edge.endVertex &&
		weight == edge.weight);
}

bool WeightedEdge::operator != (const WeightedEdge& edge) const {
	return !(*this == edge);
}

const WeightedEdge& WeightedEdge::operator=(const WeightedEdge& edge) {
	startVertex = edge.startVertex;
	endVertex = edge.endVertex;
	weight = edge.weight;
}

int WeightedEdge::getStartVertex() const {
	return startVertex;
}

int WeightedEdge::getEndVertex() const {
	return endVertex;
}

void WeightedEdge::setStartVertex(int iStartVertex) {
	if (iStartVertex < 0) throw MyException("Incorrect start vertex input");
	startVertex = iStartVertex;
}

void WeightedEdge::setEndVertex(int iEndVertex) {
	if (iEndVertex < 0) throw MyException("Incorrect start vertex input");
	endVertex = iEndVertex;
}

int WeightedEdge::getWeight() const {
	return weight;
}

void WeightedEdge::setWeight(int iWeight) {
	weight = iWeight;
}

bool WeightedEdge::isIncidental(int vertex) const {
	return (vertex == startVertex || vertex == endVertex);
}

bool WeightedEdge::isAdjacent(WeightedEdge edge) const {
	return (edge.isIncidental(startVertex) || edge.isIncidental(endVertex));
}

std::ostream& operator<<(std::ostream& out, const WeightedEdge edge) {
	out << "[(" << edge.startVertex << ", " << edge.endVertex << ") " << edge.weight << "]";
}

std::istream& operator>>(std::istream& in, WeightedEdge edge) {
	int iStartVertex;
	int iEndVertex;
	int iWeight;

	in >> iStartVertex;
	if (iStartVertex < 0) throw MyException("Incorrect start vertex");
	in >> iEndVertex;
	if (iEndVertex < 0) throw MyException("Incorrect end vertex");
	in >> iWeight;

	edge.startVertex = iStartVertex;
	edge.endVertex = iEndVertex;
	edge.weight = iWeight;
}