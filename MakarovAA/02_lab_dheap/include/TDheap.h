#ifndef _TDHEAP_
#define _TDHEAP
#include "MyExepction.h"

template<typename T>
class TDHeap {
private:
	int d;
	int maxSize;
	int currSize;
	T* data;

public:
	TDHeap(int i_d, int i_maxSize, int i_currSize, T *i_data);
	TDHeap(const TDHeap<T>& heap);
	~TDHeap();

	void insert(T i_data);
	T removeMinElm();//remove root and return it's data

	void shiftUp(int key);
	void shiftDown(int key);
	int minChild(int key) const;
	void removeMinKey();
	void heapify();

	bool isEmpty() const;
	bool isFull() const;
	
	int getCurrSize() const;

private:
	void swap(int a, int b);
};

template <typename T>
TDHeap<T>::TDHeap(int i_d, int i_maxSize, int i_currSize, T *i_data) 
		: d(i_d), maxSize(i_maxSize), currSize(i_currSize), data(i_data) {
	if (i_d <= 0 || i_maxSize <= 0 || i_currSize <= 0 || i_currSize > i_maxSize || i_data == nullptr)
		throw MyException("Incorrect data input for d-heap creation");
	data = new T[i_maxSize];
	heapify();
}

template <typename T>
TDHeap<T>::TDHeap(const TDHeap<T>& copy) 
	: d(copy.d), maxSize(copy.maxSize){
	keys = new T[copy.maxSize];
}

template <typename T>
TDHeap<T>::~TDHeap() {
	keys = nullptr;
	maxSize = 0;
	size = 0;
	d = 0;
}

template <typename T>
void TDHeap<T>::insert(T i_data) {
	if (currSize >= maxSize)
		throw MyException("Heap is full");
	data[currSize] = i_data;
	shiftUp(currSize);
	currSize++;
}

template <typename T>
void TDHeap<T>::shiftUp(int key) {
	if (key <= 0 || key > currSize - 1)
		throw MyException("Incorrect input data for shiftUp operation");
	while (i > 0) {
		int p = (i - 1) / d;
		if (data[p] > data[i]) {
			swap(i, p);
			i = p;
		}
		else break;
	}
}

template <typename T>
void TDHeap<T>::shiftDown(int key) {
	if (key <= 0 || key > currSize - 1)
		throw MyException("Incorrect input data for shiftDown operation");
	minC = minChild(key);
	i = key;
	while (minC != -1; && data[minC] < data[i]) {
		swap(minC, i);
		i = minC;
		minC = minChild(i);
	}
}

template <typename T>
int TDHeap<T>::minChild(int key) const {
	if (key < 0 || key > currSize - 1)
		throw MyException("Incorrect input data for minimal child search operation");
	if (key * d + 1 > currSize - 1) return -1;
	int firstChild = key * d + 1;
	int lastChild = (currSize - 1 > key * d + d) ? (key * d + d) : (currSize - 1);
	int minChildKey = firstChild;
	for (int i = firstChild + 1; i <= lastChild; i++)
		if (data[i] < data[minChildKey])
			minChildKey = i;
	return minChildKey;
}

template <typename T>
int TDHeap<T>::getCurrSize() const {
	return currSize;
}

template <typename T>
void TDHeap<T>::swap(int a, int b) {
	if (a >= currSize || b >= currSize || a < 0 || b < 0)
		throw MyException("Incorrect input data for transpose");
	T tmp = keys[a];
	keys[a] = keys[b];
	keys[b] = tmp;
}



#endif
