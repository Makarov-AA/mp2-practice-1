#pragma once

#include <stdlib.h>
#include <iostream>
#include "Monom.h"
#include "List.h"

class Polynom
{
private:
	enum class Symbol
	{
		variable,
		number,
		plus_minus,
		coma,
		degreeSign,
		trash,
		incorrect
	};
	TList<unsigned int, double>* monoms;
	Symbol Type(const char c);
	bool Check(std::string&);

public:
	Polynom();
	Polynom(TList<unsigned int, double>&);
	Polynom(const std::string&);
	Polynom(const Polynom&);
	~Polynom();

	const Polynom& operator=(const Polynom&);
	Polynom operator+(const Polynom&) const;
	Polynom operator-() const;
	Polynom operator-(const Polynom&) const;
	Polynom operator*(const Polynom&) const;

	Polynom operator+(const Monom&) const;
	Polynom operator-(const Monom&) const;
	Polynom operator*(const Monom&) const;

	Polynom operator+(const double) const;
	Polynom operator-(const double) const;
	Polynom operator*(const double) const;

	friend std::ostream& operator<<(std::ostream& out, const Polynom monom);
};
