#ifndef _PYRAMIDAL_SORT_
#define _PYRAMIDAL_SORT_

#define D 2

#include <iostream>

#include "TDheap.h"

template <typename T>
class PyramidalSort {
public:
	static T* pyramidalSort(T* data, int size);
};

template <typename T>
T* PyramidalSort<T>::pyramidalSort(T* data, int size) {
	TDHeap<T> sortHeap(D, size, size, data);
	T* result = new T[size];
	for (int i = 0; i < size; i++) {
		result[i] = sortHeap.getMinElm();
		sortHeap.removeMinElm();
	}
	return result;
}

#endif
