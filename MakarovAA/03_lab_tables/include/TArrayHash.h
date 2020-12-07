#pragma once
#include "THashTable.h"

template <class TKey, class TValue>
class TArrayHash : public THashTable <TKey, TValue> {
private:
	int maxSize;
	int step;
	int curr;
	TTabRecord<TKey, TValue> *arr;
public:
	TArrayHash(int _maxSize = 1000, int _step = 17) {
		maxSize = _maxSize;
		step = _step;
		arr = new TTabRecord<TKey, TValue>[maxSize];
		for (int i = 0; i < maxSize; i++)
			arr[i].setKey("");
	}
	~TArrayHash() { delete[] arr; }

	virtual void clear() {
		delete[] arr;
		arr = new TTabRecord<TKey, TValue>[maxSize];
		for (int i = 0; i < maxSize; i++)
			arr[i].setKey("");
		dataCount = 0;
	}

	bool isFull() const { return dataCount >= maxSize; }

	virtual bool findRecord(const TKey& searchKey) {
		curr = HashFunc(searchKey) % maxSize;
		int freepos = -1;
		for (int i = 0; i < maxSize; i++) {
			if (arr[curr].getKey() == "")
				if (freepos == -1)  return false;
				else {
					curr = freepos;
					return false;
				}
			if (arr[curr].getKey() == searchKey)  return true;
			if ((freepos == -1) && (arr[curr].getKey() == "&"))
				freepos = curr;
			curr = (curr + step) % maxSize;
		}
		return false;
	}

	virtual void delRecord(const TKey& iKey) {
		if (!findRecord(iKey)) return;
		arr[curr].setKey("&");
		dataCount--;
	}

	virtual bool insertRecord(const TTabRecord<TKey, TValue>& i_record) {
		if (!findRecord(i_record.getKey())) {
			arr[curr] = i_record;
			dataCount++;
			return true;
		}
		else return false;
	}

	virtual void reset() {
		curr = 0;
		while (((arr[curr].getKey() == "&") || (arr[curr].getKey() == "")) && (curr < maxSize)) {
			curr++;
		}
	}
	virtual bool isEnd() const {
		return curr >= maxSize;
	}

	virtual void goNext() {
		while ((++curr < maxSize)) {
			if (((arr[curr].getKey() != "&") && (arr[curr].getKey() != "")))
				break;
		}
	}
	virtual TTabRecord<TKey, TValue> getCurr() const { return arr[curr]; }
};