#include "SeparatedSet.h"
#include "MyException.h"

SeparatedSet::SeparatedSet(int iSize) {
	if (iSize < 0) throw MyException("Incorrect size for separated set");
	size = iSize;
	universe = new int[iSize];
	for (int i = 0; i < size; i++)
		universe[i] = -1;
}

SeparatedSet::SeparatedSet(int iSize, int *iData) {
	if (iSize < 0) throw MyException("Incorrect size for separated set");
	if (iData == nullptr) throw MyException("Data is null for separated set");
	size = iSize;
	universe = new int[iSize];
	for (int i = 0; i < iSize; i++)
		universe[i] = iData[i];
}

SeparatedSet::SeparatedSet(const SeparatedSet& copy) {
	size = copy.size;
	universe = new int[size];
	for (int i = 0; i < size; i++)
		universe[i] = copy.universe[i];
}

SeparatedSet::~SeparatedSet() {
	size = 0;
	delete[] universe;
}

void SeparatedSet::createSingleton(int newSetName) {
	if (newSetName < 0 || newSetName >= size)
		throw MyException("Incorrect set name");
	universe[newSetName] = newSetName;
}

void SeparatedSet::unite(int mainSet, int sideSet) {
	if (mainSet < 0 || mainSet >= size || sideSet < 0 || sideSet >= size)
		throw MyException("Incorrect set name for unite operation");
	for (int i = 0; i < size; i++)
		if (universe[i] == sideSet)
			universe[i] = mainSet;
}

int SeparatedSet::getSetName(int elm) {
	if (elm < 0 || elm >= size)
		throw MyException("Out of range");
	return universe[elm];
}