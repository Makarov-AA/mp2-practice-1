#pragma once

#include "TNode.h"
#include <iostream>

template <class TKey, class TData>
class TList
{
protected:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pPrev;
	TNode<TKey, TData>* pNext;
	TNode<TKey, TData>* pCurrent;

public:
	TList();
	TList(const TList& copy);
	TList(TNode<TKey, TData>* node);
	~TList();

	TNode<TKey, TData>* Search(TKey);

	void InsertStart(TKey, TData);
	void InsertStart(TNode<TKey, TData>&);
	void InsertEnd(TKey, TData);
	void InsertEnd(TNode<TKey, TData>&);
	void InsertBefore(TKey search_key, TKey, TData);
	void InsertBefore(TKey search_key, TNode<TKey, TData>&);
	void InsertAfter(TKey search_key, TKey, TData);
	void InsertAfter(TKey search_key, TNode<TKey, TData>&);

	void Remove(TKey);

	void Reset();
	void MoveNext();

	bool IsEnded() const;
	bool IsEmpty() const;

	TNode<TKey, TData>* First();
	TNode<TKey, TData>* Prev();
	TNode<TKey, TData>* Current();
	TNode<TKey, TData>* Next();

	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream& out, const TList<TKey, TData>& list);
};

template <class TKey, class TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
	pCurrent = nullptr;
}

template <class TKey, class TData>
TList<TKey, TData>::TList(const TList& copy)
{
	if (copy.pFirst == nullptr)
	{
		pFirst = nullptr;
		pPrev = nullptr;
		pNext = nullptr;
		pCurrent = nullptr;
	}
	else
	{
		pFirst = new TNode<TKey, TData>(*(copy.pFirst));
		pPrev = nullptr;
		pCurrent = pFirst;
		pNext = pFirst->pNext;
		TNode<TKey, TData>* tmp1(pFirst), *tmp2(copy.pFirst);
		while (tmp2->pNext != nullptr)
		{
			tmp1->pNext = new TNode<TKey, TData>(*(tmp2->pNext));
			tmp2 = tmp2->pNext;
			tmp1 = tmp1->pNext;
		}
		tmp1->pNext = nullptr;
	}
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pFirst = node;
	pPrev = nullptr;
	pCurrent = pFirst;
	pNext = pFirst->pNext;
}

template <class TKey, class TData>
TList<TKey, TData>::~TList()
{
	while (pFirst != nullptr)
	{
		pNext = pFirst->pNext;
		delete pFirst;
		pFirst = pNext;
	}
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key)
{
	if (pFirst == nullptr) throw "Empty list";
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp != nullptr && tmp->key != key) // && (tmp ->key != key) done
		tmp = tmp->pNext;
	if (tmp == nullptr) throw "There is no element with such a key";
	return tmp;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertStart(TKey newKey, TData newData)
{
	TNode<TKey, TData>* node = new TNode<TKey, TData>(newKey, newData);
	node->pNext = pFirst;
	pFirst = node;
	if (pCurrent == nullptr)
		pCurrent = pFirst;
	if (pCurrent == pFirst->pNext)
		pPrev = pFirst;
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertStart(TNode<TKey, TData>& node)
{
	InsertStart(node->key, node->data);
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertEnd(TKey newKey, TData newData)
{
	if (pFirst == nullptr)
	{
		pFirst = new TNode<TKey, TData>(newKey, newData);
		pCurrent = pFirst;
	}
	else
	{
		TNode<TKey, TData>* tmp = pFirst;
		while (tmp->pNext != nullptr)
			tmp = tmp->pNext;
		tmp->pNext = new TNode<TKey, TData>(newKey, newData);
		if (tmp == pCurrent)
			pNext = tmp->pNext;
		if (tmp == pPrev)
			pPrev = tmp->pNext;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertEnd(TNode<TKey, TData>& node)
{
	InsertEnd(node.key, node.data);
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey searchKey, TKey newKey, TData newData)
{
	if (pFirst == nullptr) throw "Empty list"; 
	if (pFirst->key == searchKey)
	{
		InsertStart(newKey, newData);
		return;
	}
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp->pNext != nullptr && tmp->pNext->key != searchKey) 
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr) throw "There is no element with such a key";
	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, newData);
	newNode->pNext = tmp->pNext;
	tmp->pNext = newNode;
	if (tmp == pCurrent)
		pNext = newNode;
	if (newNode->pNext == pCurrent)
		pPrev = newNode;
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey search_key, TNode<TKey, TData>& node)
{
	InsertBefore(search_key, node->key, node->data);
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey searchKey, TKey newKey, TData newData)
{
	if (pFirst == nullptr) throw "Empty list"; 
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp != nullptr && tmp->key != searchKey) 
		tmp = tmp->pNext;
	if (tmp == nullptr) throw "There is no element with such a key";
	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, newData);
	newNode->pNext = tmp->pNext;
	tmp->pNext = newNode;
	if (newNode->pNext == pCurrent)
		pPrev = newNode;
	if (tmp == pCurrent)
		pNext = newNode;
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey search_key, TNode<TKey, TData>& node)
{
	InsertAfter(search_key, node->key, node->data);
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Remove(TKey searchKey) 
{
	if (pFirst == nullptr) throw "Empty list"; 
	if (pFirst->key == searchKey)
	{
		if (pCurrent == pFirst)
		{
			pCurrent = pNext;
			if (pNext != nullptr)
				pNext = pNext->pNext;
		}
		if (pPrev == pFirst)
			pPrev = nullptr;
		TNode<TKey, TData>* tmp = pFirst->pNext;
		delete pFirst;
		pFirst = tmp;
		return;
	}
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp->pNext != nullptr && tmp->pNext->key != searchKey)
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr) throw "There is no element with such a key";
	if (pPrev == tmp->pNext) pPrev = tmp;
	if (pCurrent == tmp->pNext)
	{
		pCurrent = pNext;
		if (pNext != nullptr)
			pNext = pNext->pNext;
	}
	if (pNext == tmp->pNext)
		pNext = pNext->pNext;
	TNode<TKey, TData>* tmp1 = tmp->pNext->pNext;
	delete tmp->pNext;
	tmp->pNext = tmp1;
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Reset()
{
	if (pFirst == nullptr) throw "Empty list";
	pPrev = nullptr;
	pCurrent = pFirst;
	pNext = pFirst->pNext;
	return;
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
	return (pCurrent == nullptr); 
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEmpty() const
{
	return (pFirst == nullptr);
}

template <class TKey, class TData>
void TList<TKey, TData>::MoveNext()
{
	if (IsEnded()) throw "End of list";
	pPrev = pCurrent;
	pCurrent = pNext;
	if (pNext != nullptr)
		pNext = pNext->pNext;
	return;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::First()
{
	return pFirst;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Prev()
{
	return pPrev;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Current()
{
	return pCurrent;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Next()
{
	return pNext;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TList<TKey, TData>& list)
{
	if (list.pFirst == nullptr) throw "Empty list";
	TNode<TKey, TData>* tmp = list.pFirst;
	while (tmp != nullptr)
	{
		out << tmp << ' ';
		tmp = tmp->pNext;
	}
	return out;
}
