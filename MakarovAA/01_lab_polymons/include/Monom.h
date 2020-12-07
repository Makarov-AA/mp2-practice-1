#pragma once

#include <iostream>
#include "TNode.h"

#define Monom TNode<unsigned int, double>
#define MAX_KEY 999
#define MAX_DEG 9

template<>
struct Monom
{
	double data;
	unsigned int key;
	Monom* pNext;

	TNode() : pNext(nullptr), data(0), key(0) { };
	TNode(unsigned int iKey, double iData);
	TNode(const Monom& copy) : key(copy.key), pNext(copy.pNext), data(copy.data) { };
	~TNode() { };

	friend std::ostream& operator<<(std::ostream& out, const Monom* monom);

	const Monom& operator = (const Monom& monom);
	Monom operator + (const Monom& monom);
	Monom operator - (const Monom& monom);
	Monom operator * (const Monom& monom);
	Monom operator += (const Monom& monom);
	Monom operator -= (const Monom& monom);
	Monom operator *= (const Monom& monom);

	Monom operator -() const;

	Monom operator * (const double);

	bool operator > (const Monom& monom) const;
	bool operator >= (const Monom& monom) const;
	bool operator < (const Monom& monom) const;
	bool operator <= (const Monom& monom) const;
	bool operator == (const Monom& monom) const;
	bool operator != (const Monom& monom) const;
};