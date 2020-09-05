#ifndef SEPARATED_SET
#define SEPARATED_SET

class SeparatedSet {
	int size;
	int *universe;

public:
	SeparatedSet(int iSize);
	SeparatedSet(int iSize, int *iData);
	SeparatedSet(const SeparatedSet& copy);
	~SeparatedSet();

	void createSingleton(int newSetName);
	void unite(int mainSet, int sideSet);
	int getSetName(int elm);
};

#endif
