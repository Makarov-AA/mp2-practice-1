#pragma once
#include "TTable.h"
#include "TStack.h"

template <class TKey, class TValue>
struct TNode {
	int bal;
	TTabRecord<TKey, TValue> record;
	TNode *pLeft, *pRight;
};

template <class TKey, class TValue>
class TTreeTable : public TTable<TKey, TValue> {
protected:
	TNode<TKey, TValue> *pRoot;
	TNode<TKey, TValue> *pCurr;
	TStack<TNode<TKey, TValue>*> stack;
	TNode<TKey, TValue> **pRes;
	int pos;

public:
	TTreeTable() {
		pRoot = pCurr = NULL;
	}

	virtual bool findRecord(const TKey& searchKey) {
		pRes = &pRoot;
		while (*pRes != NULL) {
			if ((*pRes)->record.getKey() == searchKey)
				return true;
			if ((*pRes)->record.getKey() < searchKey)
				pRes = &(*pRes)->pRight;
			else pRes = &(*pRes)->pLeft;
		}
		return false;
	}

	virtual bool insertRecord(const TTabRecord<TKey, TValue>& i_record) {
		if (!findRecord(i_record.getKey())) {
			*pRes = new TNode<TKey, TValue>();
			(*pRes)->record = i_record;
			dataCount++;
			return true
		}
		else return false;
	}

	virtual void delRecord(const TKey& iKey) {
		if (!findRecord(iKey)) return;
		TNode<TKey, TValue> *tmp = *pRes;
		if (!tmp->pLeft)
			*pRes = tmp->pRight;
		else if (!tmp->pRight)
			*pRes = tmp->pLeft;

		else {
			TNode<TKey, TValue> *find = tmp->pLeft;
			TNode<TKey, TValue> **iter;
			iter = &(*pRes)->pLeft;
			while (find->pRight) {
				iter = &(*iter)->pRight;
				find = find->pRight;
			}
			tmp->record = find->record;
			tmp = find;
			*iter = find->pLeft;
		}
		dataCount--;
		delete tmp;
	}

	virtual void clear() {
		if (dataCount == 0) return;
		TStack<TNode<TKey, TValue>*> st;
		st.clear();
		for (Reset(); !isEnd(); goNext())
			st.push(pCurr);
		while (!st.isEmpty())
			delete st.pop();
		dataCount = 0;
		pCurr = pRoot = nullptr;
	}
	virtual void reset(){
		stack.clear();
		pos = 0;
		pCurr = pRoot;
		while (pCurr->pLeft != NULL) {
			stack.push(pCurr);
			pCurr = pCurr->pLeft;
		}

	}
	virtual bool isEnd() const {
		return pos == dataCount;
	}

	virtual void goNext() {
		pos++;
		if (pCurr->pRight != NULL) {
			pCurr = pCurr->pRight;
			while (pCurr->pLeft != NULL) {
				stack.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		else if (!stack.isEmpty()) pCurr = stack.pop();
	}

	virtual bool isFull() const {
		return false;
	}

	virtual TTabRecord<TKey, TValue> getCurr() const { return pCurr->record; }
};

