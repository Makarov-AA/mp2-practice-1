#ifndef TTABRECORD_H
#define TTABRECORD_H

#include <iostream>
#include <vector>

template<typename TKey, class TData>
class TTabRecord {
protected:
	TKey key;
	TData data;
public:
	TTabRecord(const TKey iKey = {}, TData iData = {});
	TTabRecord(const TTabRecord& copy);
	void setKey(const TKey iKey);
	TKey getKey() const;
	void setValue(TData iData);
	TData getValue() const;
	const TTabRecord& operator = (const TTabRecord& tabRecord);
};

template<typename TKey, class TData>
TTabRecord<TKey, TData>::TTabRecord(const TKey iKey, TData iData) {
	key = iKey;
	data = iData;
}

template<typename TKey, class TData>
TTabRecord<TKey, TData>::TTabRecord(const TTabRecord& copy) {
	key = copy.key;
	data = copy.data;
}

template<typename TKey, class TData>
void TTabRecord<TKey, TData>::setKey(const TKey iKey) {
	key = iKey;
}

template<class TKey, class TData>
TKey TTabRecord<TKey, TData>::getKey() const {
	return key;
}

template<typename TKey, class TData>
void TTabRecord<TKey, TData>::setValue(TData iData) {
	data = iData;
}

template<typename TKey, class TData>
TData TTabRecord<TKey, TData>::getValue() const {
	return data;
}

template<typename TKey, class TData>
const TTabRecord<TKey, TData>& TTabRecord<TKey, TData>::operator = (const TTabRecord& tabRecord) {
	key = tabRecord.key;
	data = tabRecord.data;
}

#endif
