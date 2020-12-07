#pragma once
#include "TArrayTable.h"

template <class TKey, class TValue>
class TSortTable : public TArrayTable<TKey, TValue> {
public:
	virtual bool findRecord(const TKey& searchKey) {
		int left = 0, right = dataCount - 1, middle;
		while (left <= right) {
			middle = (left + right) / 2;
			if (arr[middle].getKey() == searchKey) {
				curr = middle;
				return true;
			}

			if (arr[middle].getKey() < searchKey) left = middle + 1;
			else right = middle - 1;
		}
		curr = left;
		return false;
	}
	virtual bool insertRecord(const TTabRecord<TKey, TValue>& i_record) {

		if (!findRecord(i_record.getKey())) {
			if (isFull()) return false;
			for (int i = dataCount; i > curr; i--) {
				arr[i] = arr[i - 1];
			}
			arr[curr] = record;
			dataCount++;
			return true;
		}
		else {
			return false;
		}
	}
	virtual void delRecord(const TKey& iKey) {
		if (findRecord(iKey)) {
			for (int i = curr; i < dataCount - 1; i++) {
				arr[i] = arr[i + 1];
			}
			dataCount--;
		}
	}

	virtual void clear() {
		if (dataCount <= 0) return;
		delete[] arr;
		arr = new TTabRecord<TKey, TValue>[maxSize];
		dataCount = 0;
	}
	void QuickSort(int left, int right) {
		int middle = (left + right) / 2;
		TKey x = arr[middle].getKey();
		TTabRecord<TKey, TValue> tmp;
		int i = left, j = right - 1;

		while (i <= j) {
			while (arr[i].getKey() < x) {
				i++;
			}
			while (arr[j].getKey() > x) {
				j--;
			}

			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}

			if (j > left) {
				QuickSort(left, j);
			}
			if (i < right) {
				QuickSort(i, right);
			}
		}
	}
};
