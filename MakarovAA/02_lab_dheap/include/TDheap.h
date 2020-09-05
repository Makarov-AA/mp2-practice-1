#ifndef _TDHEAP_
#define _TDHEAP
#include "MyException.h"
#include <iostream>

template<typename T>
class TDHeap {
private:
	int d;
	int maxSize;
	int currSize;
	

public:
	T* data;
	TDHeap(int i_d, int i_maxSize, int i_currSize, T *i_data);
	TDHeap(const TDHeap<T>& heap);
	~TDHeap();

	void insert(T i_data);
	void removeMinElm();

	T getMinElm() const;

	void shiftUp(int key);
	void shiftDown(int key);
	void heapify();

	bool isEmpty() const;
	bool isFull() const;

	int getCurrSize() const;

private:
	void swap(int a, int b);
	int minChild(int key) const;
};

template <typename T>
TDHeap<T>::TDHeap(int i_d, int i_maxSize, int i_currSize, T *i_data) 
		: d(i_d), maxSize(i_maxSize), currSize(i_currSize), data(i_data) {
	if (i_d <= 0 || i_maxSize <= 0 || i_currSize <= 0 || i_currSize > i_maxSize || i_data == nullptr)
		throw MyException("Incorrect data input for d-heap creation");
	data = new T[i_maxSize];
	for (int i = 0; i < currSize; i++)
		data[i] = i_data[i];
	heapify();
}

template <typename T>
TDHeap<T>::TDHeap(const TDHeap<T>& copy) 
	: d(copy.d), maxSize(copy.maxSize){
	data = new T[copy.maxSize];
}

template <typename T>
TDHeap<T>::~TDHeap() {
	data = nullptr;
	maxSize = 0;
	currSize = 0;
	d = 0;
}

template <typename T>
void TDHeap<T>::insert(T i_data) {
	if (isFull()) throw MyException("Heap is full");
	data[currSize] = i_data;
	shiftUp(currSize);
	currSize++;
}

template <typename T>
void TDHeap<T>::removeMinElm() {
	if (isEmpty()) throw MyException("Heap is empty");
	swap(currSize - 1, 0);
	currSize--;
	shiftDown(0);
}

template <typename T>
T TDHeap<T>::getMinElm() const {
	if (isEmpty()) throw MyException("Heap is empty");
	return data[0];
}

template <typename T>
void TDHeap<T>::shiftUp(int key) {
	if (key <= 0 || key > currSize)
		throw MyException("Incorrect input data for shiftUp operation");
	while (key > 0) {
		int p = (key - 1) / d;
		if (data[p] > data[key]) {
			swap(key, p);
			key = p;
		}
		else break;
	}
}

template <typename T>
void TDHeap<T>::shiftDown(int key) {
	if (key < 0 || key > currSize)
		throw MyException("Incorrect input data for shiftDown operation");
	int minC = minChild(key);
	while (minC != -1 && data[minC] < data[key]) {
		swap(minC, key);
		key = minC;
		minC = minChild(key);
	}
}

template <typename T>
void TDHeap<T>::heapify() {
	for (int i = currSize - 1; i >= 0; i--)
		shiftDown(i);
}

template <typename T>
bool TDHeap<T>::isEmpty() const {
	return (currSize == 0);
}

template <typename T>
bool TDHeap<T>::isFull() const {
	return (currSize == maxSize);
}

template <typename T>
int TDHeap<T>::getCurrSize() const {
	return currSize;
}

template <typename T>
void TDHeap<T>::swap(int a, int b) {
	if (a >= currSize || b >= currSize || a < 0 || b < 0)
		throw MyException("Incorrect input data for transpose");
	T tmp = data[a];
	data[a] = data[b];
	data[b] = tmp;
}

template <typename T>
int TDHeap<T>::minChild(int key) const {
	if (key < 0 || key > currSize)
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

#endif
