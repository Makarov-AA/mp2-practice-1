#include "Polynom.h"

Polynom::Symbol Polynom::Type(const char c)
{
	if (c == 'x' || c == 'y' || c == 'z') return Symbol::variable;
	if (c >= '0' && c <= '9') return Symbol::number;
	if (c == '-' || c == '+') return Symbol::plus_minus;
	if (c == '.' || c == ',') return Symbol::coma;
	if (c == '^') return Symbol::degreeSign;
	if (c == ' ' || c == '*') return Symbol::trash;
	return Symbol::incorrect;
}

bool Polynom::Check(std::string &expr)
{
	if (expr.size() == 0) return false;
	int i = 0;
	while (i < expr.size()) //удаление символов ' ' и '*'
	{
		switch (Type(expr[i]))
		{
		case Symbol::incorrect:
			return false;
			break;
		case Symbol::trash:
			expr.erase(i, 1);
			break;
		default:
			i++;
		}
	}
	if (Type(expr[0]) <= Symbol::plus_minus)//Проверка первого символа
	{
		if ((Type(expr[0]) != Symbol::plus_minus))
			expr.insert(0, 1, '+');
		else if (Type(expr[1]) > Symbol::number) return false;
	}
	else return false;
	for (int i = 1; i < expr.size(); i++)
		switch (Type(expr[i]))
		{
		case Symbol::plus_minus: //проверка, что до и после + или - стоит переменная или цифра
			if (Type(expr[i - 1]) > Symbol::number || Type(expr[i + 1]) > Symbol::number)
				return false;
			break;
		case Symbol::degreeSign: //проверка, что степень представлена единственным числом
			if (Type(expr[i - 1]) != Symbol::variable && Type(expr[i + 1]) != Symbol::number)
				if (Type(expr[i + 2]) == Symbol::number || Type(expr[i + 2]) == Symbol::coma)
					return false;
				else return false;
			break;
		case Symbol::coma: //проверка, что запятая (точка) разделяет два числа
			if (Type(expr[i - 1]) != Symbol::number || Type(expr[i + 1]) != Symbol::number)
				return false;
			break;
		}
	return true;
}

Polynom::Polynom()
{
	monoms = new TList<unsigned int, double>;
}

Polynom::Polynom(TList<unsigned int, double>& list)
{
	monoms = new TList<unsigned int, double>;
	if (list.IsEmpty()) return;
	list.Reset();
	while (!list.IsEnded())
	{
		if (list.Current()->data != 0.)
			*this = *this + *(list.Current());
		list.MoveNext();
	}
}

Polynom::Polynom(const std::string& iExpr)
{
	std::string expr(iExpr);
	if (!Check(expr)) throw "Incorrect input";
	monoms = new TList<unsigned int, double>;
	for (int i = 0; i < expr.size(); i++)
	{
		bool minus = (expr[i] == '-');
		unsigned int degree = 0;
		double coef;
		if (Type(expr[i + 1]) == Symbol::variable)//считывание коэффициента
			if (minus) coef = -1;
			else coef = 1;
		else
		{
			std::string sCoef;
			if (minus) sCoef += '-';
			while (Type(expr[i + 1]) == Symbol::number)
			{
				sCoef += expr[i + 1];
				i++;
			}
			if (Type(expr[i + 1]) == Symbol::coma)
			{
				sCoef += '.';
				i++;
				while (Type(expr[i + 1]) == Symbol::number)
				{
					sCoef += expr[i + 1];
					i++;
				}
			}
			coef = std::strtod(sCoef.c_str(), nullptr);
		}
		if (Type(expr[i + 1]) == Symbol::variable) //считывание степеней переменных
			while (i < expr.size() && Type(expr[i + 1]) != Symbol::plus_minus)
				switch (expr[i + 1])
				{
				case 'x':
					i++;
					if (Type(expr[i + 1]) == Symbol::degreeSign)
					{
						i++;
						degree += ((unsigned int)expr[i + 1] - 48) * 100;
						i++;
					}
					else degree += 100;
					break;
				case 'y':
					i++;
					if (Type(expr[i + 1]) == Symbol::degreeSign)
					{
						i++;
						degree += ((unsigned int)expr[i + 1] - 48) * 10;
						i++;
					}
					else degree += 10;
					break;
				case 'z':
					i++;
					if (Type(expr[i + 1]) == Symbol::degreeSign)
					{
						i++;
						degree += (unsigned int)expr[i + 1] - 48;
						i++;
					}
					else degree += 1;
					break;
				case '\0':
					i++;
					break;
				default:
					throw "Not a variable";
					break;
				}
		if (coef != 0)
		{
			Monom newMonom(degree, coef);
			*this = *this + newMonom;
		}
	}
}

Polynom::Polynom(const Polynom& copy)
{
	monoms = new TList<unsigned int, double>(*(copy.monoms));
}

Polynom::~Polynom()
{
	delete monoms;
}

const Polynom& Polynom::operator=(const Polynom& polynom)
{
	if (&polynom == this) return *this;
	delete monoms;
	monoms = new TList<unsigned int, double>(*polynom.monoms);
	return *this;
}

Polynom Polynom::operator+(const Polynom& polynom) const
{
	if (monoms->IsEmpty())
		return polynom;
	if (polynom.monoms->IsEmpty())
		return *this;
	Polynom sum;
	monoms->Reset();
	polynom.monoms->Reset();
	while (!monoms->IsEnded() && !polynom.monoms->IsEnded())
	{
		if (monoms->Current()->key == polynom.monoms->Current()->key)
		{
			Monom monomSum = *monoms->Current() + *polynom.monoms->Current();
			if (monomSum.data != 0)
				sum.monoms->InsertEnd(monomSum);
			monoms->MoveNext();
			polynom.monoms->MoveNext();
		}
		else if (monoms->Current()->key > polynom.monoms->Current()->key)
		{
			sum.monoms->InsertEnd(*monoms->Current());
			monoms->MoveNext();
		}
		else
		{
			sum.monoms->InsertEnd(*polynom.monoms->Current());
			polynom.monoms->MoveNext();
		}
	}
	while (!monoms->IsEnded())
	{
		sum.monoms->InsertEnd(*monoms->Current());
		monoms->MoveNext();
	}
	while (!polynom.monoms->IsEnded())
	{
		sum.monoms->InsertEnd(*polynom.monoms->Current());
		polynom.monoms->MoveNext();
	}
	return sum;
}

Polynom Polynom::operator-() const
{
	if (monoms->IsEmpty()) return Polynom();
	Polynom minus(*this);
	minus.monoms->Reset();
	while (!minus.monoms->IsEnded())
	{
		minus.monoms->Current()->data *= -1;
		minus.monoms->MoveNext();
	}
	return minus;
}

Polynom Polynom::operator-(const Polynom& polynom) const
{
	return *this + (-polynom);
}

Polynom Polynom::operator*(const Polynom& polynom) const
{
	if (monoms->IsEmpty() || polynom.monoms->IsEmpty()) return Polynom();
	monoms->Reset();
	Polynom result;
	Monom tmpMonom1, tmpMonom2;
	while (!monoms->IsEnded())
	{
		tmpMonom1 = *monoms->Current();
		polynom.monoms->Reset();
		Polynom tmpPolynom;
		while (!polynom.monoms->IsEnded())
		{
			tmpMonom2 = tmpMonom1 * (*polynom.monoms->Current());
			tmpPolynom.monoms->InsertEnd(tmpMonom2);
			polynom.monoms->MoveNext();
		}
		result = result + tmpPolynom;
		monoms->MoveNext();
	}
	return result;
}

Polynom Polynom::operator+(const Monom& monom) const
{
	Polynom sum(*this);
	if (sum.monoms->IsEmpty())
	{
		sum.monoms->InsertStart(monom.key, monom.data);
		return sum;
	}
	sum.monoms->Reset();
	while (!sum.monoms->IsEnded() && sum.monoms->Current()->key > monom.key)
		sum.monoms->MoveNext();
	if (sum.monoms->IsEnded()) {
		sum.monoms->InsertEnd(monom.key, monom.data);
		return sum;
	}
	if (sum.monoms->Current()->key == monom.key)
	{
		*(sum.monoms->Current()) += monom;
		if (sum.monoms->Current()->data == 0) sum.monoms->Remove(sum.monoms->Current()->key);
		return sum;
	}
	if (sum.monoms->Current()->key < monom.key)
	{
		sum.monoms->InsertBefore(sum.monoms->Current()->key, monom.key, monom.data);
		return sum;
	}

}

Polynom Polynom::operator-(const Monom& monom) const
{
	return *this + (-monom);
}

Polynom Polynom::operator*(const Monom& monom) const
{
	if (monom.data == 0) return Polynom();
	Polynom mlp(*this);
	mlp.monoms->Reset();
	while (!mlp.monoms->IsEnded())
	{
		*(mlp.monoms->Current()) *= monom;
		mlp.monoms->MoveNext();
	}
	return mlp;
}

Polynom Polynom::operator+(const double c) const
{
	if (c == 0) return *this;
	Polynom c0;
	c0.monoms->InsertEnd(0, c);
	return *this + c0;
}

Polynom Polynom::operator-(const double c) const
{
	return *this + (-c);
}

Polynom Polynom::operator*(const double c) const
{
	if (c == 0)
		return Polynom();
	Polynom mlp(*this);
	mlp.monoms->Reset();
	while (!mlp.monoms->IsEnded())
	{
		*mlp.monoms->Current() = *mlp.monoms->Current() * c;
		mlp.monoms->MoveNext();
	}
	return mlp;
}

std::ostream& operator<<(std::ostream& out, const Polynom polynom)
{
	if (polynom.monoms->IsEmpty())
	{
		out << "0";
		return out;
	}
	polynom.monoms->Reset();
	out << polynom.monoms->Current();
	polynom.monoms->MoveNext();
	while (!polynom.monoms->IsEnded())
	{
		if (polynom.monoms->Current()->data > 0)
			out << '+';
		out << polynom.monoms->Current();
		polynom.monoms->MoveNext();
	}
	return out;
}