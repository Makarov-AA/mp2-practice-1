#ifndef TARRAYTABLE_H
#define TARRAYTABLE_H

#define TABLEFAULTSIZE 25

#include "TArrayTable.h"

template <class TKey, class TValue>
class TScanTable :public TArrayTable<TKey, TValue> {
public:
	virtual bool findRecord(const TKey& searchKey) {
		for (int i = 0; i < dataCount; i++) {
			if (arr[i].getKey() == searchKey) {
				curr = i;
				return true;
			}
		}
		curr = dataCount;
		return false;
	}
	virtual bool insertRecord(const TTabRecord<TKey, TValue>& i_record) {

		if (!findRecord(i_record.getKey())) {
			if (isFull()) return false;
			arr[curr] = record;
			dataCount++;
			return true;
		}
		else {
			return false;
		}
	}

	virtual void clear() {
		if (dataCount <= 0) return;
		delete[] arr;
		arr = new TRecord<TKey, TValue>[maxSize];
		dataCount = 0;
	}

	virtual void delRecord(const TKey& iKey) {

		if (findRecord(iKey)) {
			arr[curr] = arr[--dataCount];
		}
	}
};

#endif