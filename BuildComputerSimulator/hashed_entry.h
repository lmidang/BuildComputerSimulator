#pragma once
#include "entry.h"

template <typename KeyType, typename ItemType>
class HashedEntry : public Entry<KeyType, ItemType> {
private:
	HashedEntry<KeyType, ItemType> *pNext;

public:
	HashedEntry();
	HashedEntry(KeyType, ItemType);
	HashedEntry(KeyType, ItemType, HashedEntry<KeyType, ItemType> *);

	HashedEntry<KeyType, ItemType> * getNext() const;
	void setNext(HashedEntry<KeyType, ItemType> *);
};

template <typename KeyType, typename ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry() : Entry(), pNext(nullptr) {}

template <typename KeyType, typename ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType sk, ItemType ni) :
	Entry<KeyType, ItemType>::Entry(sk, ni), pNext(nullptr) {}

template <typename KeyType, typename ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType sk, ItemType ni, HashedEntry<KeyType, ItemType> *pn) :
	Entry<KeyType, ItemType>::Entry(sk, ni), pNext(pn) {}

template <typename KeyType, typename ItemType>
HashedEntry<KeyType, ItemType> * HashedEntry<KeyType, ItemType>::getNext() const {
	return pNext;
}

template <typename KeyType, typename ItemType>
void HashedEntry<KeyType, ItemType>::setNext(HashedEntry<KeyType, ItemType> *pn) {
	pNext = pn;
}