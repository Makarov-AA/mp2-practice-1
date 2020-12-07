#ifndef TTABLE_H
#define TTABLE_H
#include "MyExceptions.h"
#include "TTabRecord.h"

template <typename TKey, class TValue>
class TTable {
protected:
	int dataCount;

public:
	TTable() : dataCount(0) {};
	virtual ~TTable() {};

	int getDataCount() const {
		return dataCount;
	}

	bool isEmpty() const {
		return (dataCount <= 0);
	}

	virtual bool isFull() const = 0;

	virtual bool findRecord(const TKey& searchKey) = 0;
	virtual bool insertRecord(const TTabRecord<TKey, TValue>& i_record) = 0;
	virtual void delRecord(const TKey& iKey) = 0;
	virtual void reset() = 0;
	virtual bool isEnd() const = 0;
	virtual void goNext() = 0;
	virtual TTabRecord<TKey, TValue> getCurr() const = 0;

	virtual void clear() = 0;
};
#endif
