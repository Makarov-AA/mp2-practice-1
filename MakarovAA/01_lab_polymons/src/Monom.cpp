#include "Monom.h"

Monom::TNode(unsigned int iKey, double iData) : key(iKey), pNext(nullptr), data(iData)
{
	if (iKey > MAX_KEY) throw "Incorrect degrees";
}

const Monom& Monom::operator = (const Monom& monom)
{
	if (&monom == this) return *this;
	data = monom.data;
	key = monom.key;
	return *this;
}

Monom Monom::operator + (const Monom& monom)
{
	if (key != monom.key) throw "Different degrees";
	return Monom(key, data + monom.data);
}

Monom Monom::operator - (const Monom& monom)
{
	if (key != monom.key) throw "Different degrees";
	return Monom(key, data - monom.data);
}

Monom Monom::operator * (const Monom& monom)
{
	if ((key % 10 + monom.key % 10) > 9) throw "Out of degree's size";
	if (((key % 100) / 10 + (monom.key % 100) / 10) > 9) throw "Out of degree's size";
	if ((key / 100 + monom.key / 100) > 9) throw "Out of degree's size";
	return Monom(key + monom.key, data * monom.data);
}

Monom Monom::operator += (const Monom& monom)
{
	*this = *this + monom;
	return *this;
}

Monom Monom::operator -= (const Monom& monom)
{
	*this = *this - monom;
	return *this;
}

Monom Monom::operator *= (const Monom& monom)
{
	*this = *this * monom;
	return *this;
}

Monom Monom::operator -() const
{
	return Monom(key, data * -1.);
}

Monom Monom::operator * (const double c)
{
	return Monom(key, data * c);
}

bool Monom::operator > (const Monom& monom) const
{
	return key > monom.key;
}

bool Monom::operator < (const Monom& monom) const
{
	return key < monom.key;
}

bool Monom::operator >= (const Monom& monom) const
{
	return key >= monom.key;
}

bool Monom::operator <= (const Monom& monom) const
{
	return key <= monom.key;
}

bool Monom::operator == (const Monom& monom) const
{
	return (key == monom.key && data == monom.data);
}

bool Monom::operator != (const Monom& monom) const
{
	return (key == monom.key && data != monom.data);
}

std::ostream& operator<<(std::ostream& out, const Monom* monom)
{
	if (monom == nullptr) throw "nullptr monom";
	if (monom->key == 0)
	{
		out << monom->data;
		return out;
	}
	if (monom->data != 1)
		if (monom->data != -1)
			out << monom->data;
		else out << '-';
	if (monom->key / 100 > 0)
		if (monom->key / 100 == 1)
			out << 'x';
		else
			out << "x^" << monom->key / 100;
	if ((monom->key % 100) / 10 > 0)
		if ((monom->key % 100) / 10 == 1)
			out << 'y';
		else
			out << "y^" << (monom->key % 100) / 10;
	if (monom->key % 10 > 0)
		if (monom->key % 10 == 1)
			out << 'z';
		else
			out << "z^" << monom->key % 10;
	return out;
}