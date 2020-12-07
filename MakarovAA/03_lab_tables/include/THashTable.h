#pragma once
#include "TTable.h"
template <class TKey, class TValue>
class THashTable : public TTable<TKey, TValue> {
protected:
	int HashFunc(const TKey& key) {
		int pos = 0;
		for (int i = 0; i < key.size(); i++)
			pos += key[i] << i;
		return pos;
	}
};
