#pragma once
#include "TTable.h"

template <class TKey, class TValue>
class TArrayTable : public TTable<TKey, TValue> {
protected:
	TTabRecord <TKey, TValue> *arr;
	int maxSize;
	int curr;
public:
	TArrayTable(int _maxSize = 1000) {
		maxSize = _maxSize;
		arr = new TTabRecord<TKey, TValue>[maxSize];
		curr = 0;
	}
	~TArrayTable() { delete[] arr; }
	virtual bool isFull() const { return dataCount == maxSize; }
	virtual TTabRecord<TKey, TValue> getCurr() const { return arr[curr]; }
	virtual void reset() { curr = 0; }
	virtual bool isEnd() const { return curr == dataCount; }
	virtual void goNext() { curr++; }
};