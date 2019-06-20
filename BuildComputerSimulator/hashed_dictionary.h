#pragma once
#include "hashed_entry.h"

template <typename KeyType, typename ItemType>
class HashedDictionary {
private:
	HashedEntry<KeyType, ItemType> **hashTable;
	size_t itemCount;
	const size_t hashTableSize;
	static const size_t DEFAULT_SIZE;

	size_t getHashIndex(const unsigned int &) const;
	size_t getHashIndex(const std::string &) const;
	static bool isPrime(size_t);

	int loadFactor;

public:
	class OutOfRangeException {};

	HashedDictionary();
	HashedDictionary(size_t);
	~HashedDictionary();

	void clear();
	bool isEmpty() const;
	size_t getNumberOfItems() const;
	size_t getSize();
	int getLoadFactor();

	bool add(const KeyType &, const ItemType &);
	bool remove(const KeyType &);

	ItemType getItem(const KeyType &);
	bool contains(const KeyType &);
	void traverse(void visit(const ItemType &));
	void traverseMod(void visit(ItemType &));
	void traverseIndex(void visit(const ItemType &), size_t);
};

template <typename KeyType, typename ItemType>
const size_t HashedDictionary<KeyType, ItemType>::DEFAULT_SIZE = 53;

template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary() :
	itemCount(0), hashTableSize(DEFAULT_SIZE) {
	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];
	
	for (size_t i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(size_t hts) :
	itemCount(0), hashTableSize(hts) {
	if (!isPrime(hts))
		throw "Hash table size isn't prime!";

	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];

	for (size_t i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary() {
	clear();

	delete[] hashTable;
	hashTable = nullptr;
}

template <typename KeyType, typename ItemType>
void HashedDictionary<KeyType, ItemType>::clear() {
	for (size_t i = 0; i < hashTableSize; i++) {
		HashedEntry<KeyType, ItemType> *pCur = hashTable[i];
		HashedEntry<KeyType, ItemType> *pNext;

		while (pCur != nullptr) {
			pNext = pCur->getNext();
			delete pCur;
			pCur = pNext;
		}

		hashTable[i] = nullptr;
	}

	itemCount = 0;
}

template <typename KeyType, typename ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const {
	return !itemCount;
}

template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getNumberOfItems() const {
	return itemCount;
}

template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getSize() {
	return hashTableSize;
}

template <typename KeyType, typename ItemType>
int HashedDictionary<KeyType, ItemType>::getLoadFactor() {
	return loadFactor;
}


template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getHashIndex(const unsigned int &searchKey) const {
	searchKey = ((searchKey >> 16) ^ searchKey) * 0x45d9f3b;
	searchKey = ((searchKey >> 16) ^ searchKey) * 0x45d9f3b;
	searchKey = (searchKey >> 16) ^ searchKey;

	return searchKey % hashTableSize;
}

template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getHashIndex(const std::string &searchKey) const {
	unsigned long hash = 5381;

	for (size_t i = 0; i < searchKey.length(); i++)
		hash = ((hash << 5) + hash) + searchKey[i];

	return hash % hashTableSize;
}

template <typename KeyType, typename ItemType>
bool HashedDictionary<KeyType, ItemType>::isPrime(size_t num) {
	for (size_t i = 2; i * i <= num; i++) {
		if (num % i == 0)
			return false;
	}
	
	return true;
}

template <typename KeyType, typename ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem) {
	HashedEntry<KeyType, ItemType> *pEntryToAdd = new HashedEntry<KeyType, ItemType>(searchKey, newItem);

	size_t itemHashIndex = getHashIndex(searchKey);
	loadFactor++;

	if (hashTable[itemHashIndex] == nullptr) {
		hashTable[itemHashIndex] = pEntryToAdd;
		loadFactor++;
	}
	else {
		pEntryToAdd->setNext(hashTable[itemHashIndex]);
		loadFactor++;

		hashTable[itemHashIndex] = pEntryToAdd;
		loadFactor++;
	}

	itemCount++;

	return true;
}

template <typename KeyType, typename ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) {
	bool itemFound = false;

	size_t itemHashIndex = getHashIndex(searchKey);

	if (hashTable[itemHashIndex] != nullptr) {
		if (searchKey == hashTable[itemHashIndex]->getKey()) {
			HashedEntry<KeyType, ItemType> *pEntryToRemove = hashTable[itemHashIndex];
			hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
			delete pEntryToRemove;
			pEntryToRemove = nullptr;
			itemFound = true;
		}
		else {
			HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
			HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();

			while (pCurr != nullptr && !itemFound) {
				if (searchKey == pCurr->getKey()) {
					pPrev->setNext(pCurr->getNext());
					delete pCurr;
					pCurr = nullptr;
					itemFound = true;
					itemCount--;
				}
				else {
					pPrev = pCurr;
					pCurr = pCurr->getNext();
				}
			}
		}
	}

	return itemFound;
}

template <typename KeyType, typename ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) {
	size_t itemHashIndex = getHashIndex(searchKey);

	if (hashTable[itemHashIndex] != nullptr) {
		if (searchKey == hashTable[itemHashIndex]->getKey())
			return hashTable[itemHashIndex]->getItem();

		HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
		HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();

		while (pCurr != nullptr) {
			if (searchKey == pCurr->getKey()) {
				pPrev->setNext(pCurr->getNext());
				pCurr->setNext(hashTable[itemHashIndex]);
				hashTable[itemHashIndex] = pCurr;
				return pCurr->getItem();
			}
			else {
				pPrev = pCurr;
				pCurr = pCurr->getNext();
			}
		}
	}

	throw "Item not found!";
}

template <typename KeyType, typename ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType &searchKey) {
	size_t itemHashIndex = getHashIndex(searchKey);

	if (hashTable[itemHashIndex] != nullptr) {
		if (searchKey == hashTable[itemHashIndex]->getKey())
			return true;

		HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
		HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();

		while (pCurr != nullptr) {
			if (searchKey == pCurr->getKey()) {
				pPrev->setNext(pCurr->getNext());
				pCurr->setNext(hashTable[itemHashIndex]);
				hashTable[itemHashIndex] = pCurr;
				return true;
			}
			else {
				pPrev = pCurr;
				pCurr = pCurr->getNext();
			}
		}
	}

	return false;
}

template <typename KeyType, typename ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(const ItemType &)) {
	for (size_t i = 0; i < hashTableSize; i++) {
		HashedEntry<KeyType, ItemType> *pCurr = hashTable[i];

		while (pCurr != nullptr) {
			visit(pCurr->getItem());
			pCurr = pCurr->getNext();
		}
	}
}

template <typename KeyType, typename ItemType>
void HashedDictionary<KeyType, ItemType>::traverseMod(void visit(ItemType &)) {
	for (size_t i = 0; i < hashTableSize; i++) {
		HashedEntry<KeyType, ItemType> *pCurr = hashTable[i];

		while (pCurr != nullptr) {
			visit(pCurr->getItem());
			pCurr = pCurr->getNext();
		}
	}
}


template <typename KeyType, typename ItemType>
void HashedDictionary<KeyType, ItemType>::traverseIndex(void visit(const ItemType &), size_t i) {
	if (i >= hashTableSize) {
		throw HashedDictionary<KeyType, ItemType>::OutOfRangeException();
	}
	HashedEntry<KeyType, ItemType> *pCurr = hashTable[i];

	while (pCurr != nullptr) {
		visit(pCurr->getItem());
		pCurr = pCurr->getNext();
	}
}