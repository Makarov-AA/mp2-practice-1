#include "Label.h"
#include "MyException.h"

Label::Label(){
	distance = 0;
	vertex = -1;
}

Label::Label(int iVertex, int iDistance){
	if (iVertex < 0)
		throw MyException("Vertex value must be non-negative");
	if (iDistance < 0)
		throw MyException("Distance must be non-negative");
	distance = iDistance;
	vertex = iVertex;
}

int Label::getVertex() const{
	return vertex;
}

int Label::getDistance() const{
	return distance;
}

void Label::setVertex(int iVertex){
	if (iVertex < 0)
		throw MyException("Vertex value must be non-negative");
	vertex = iVertex;
}

void Label::setDistance(int iDistance){
	if (iDistance < 0)
		throw MyException("Distance must be non-negative");
	distance = iDistance;
}

bool Label::operator>(const Label& label) const{
	return (distance > label.distance);
}

bool Label::operator<(const Label& label) const{
	return (distance < label.distance);
}

bool Label::operator>=(const Label& label) const{
	return (distance >= label.distance);
}

bool Label::operator<=(const Label& label) const{
	return (distance <= label.distance);
}

bool Label::operator==(const Label& label) const{
	if ((distance == label.distance) && (vertex == label.vertex))
		return true;
	return false;
}

bool Label::operator!=(const Label& label) const{
	return !(label == *this);
}

const Label& Label::operator=(const Label& label)
{
	if (*this == label)
		return *this;
	setVertex(label.getVertex());
	setDistance(label.getDistance());
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Label& label)
{
	out << "Vertex: " << label.getVertex() << "   ";
	out << "Distance: " << label.getDistance() << "   ";
	return out;
}

std::istream& operator>>(std::istream& in, Label& label)
{
	int iDistance = 0;
	int iVertex = -1;

	std::cout << "Enter vertex: ";
	in >> iVertex;
	if (iVertex < 0)
		throw MyException("Vertex value must be non-negative");
	label.vertex = iVertex;

	std::cout << "Enter distance: ";
	in >> iDistance;
	if (iDistance < 0)
		throw MyException("Distance must be non-negative");
	label.distance = iDistance;

	return in;
};