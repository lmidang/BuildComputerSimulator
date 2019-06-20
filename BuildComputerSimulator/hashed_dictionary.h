/*
Worked on by Bennett Zhang
*/

#pragma once
#include "hashed_entry.h"

template <typename KeyType, typename ItemType>
class HashedDictionary {
private:
	HashedEntry<KeyType, ItemType> **hashTable; // An array of linked lists
	size_t itemCount; // The number of items in the HashedDictionary
	const size_t hashTableSize; // The size of the array
	static const size_t DEFAULT_SIZE; // The default size of the array, if none is specified

	// Hash functions
	size_t getHashIndex(const unsigned int &) const;
	size_t getHashIndex(const std::string &) const;

	// Checks if a number is prime
	static bool isPrime(size_t);

	// Efficiency
	int loadFactor;

public:
	class OutOfRangeException {};

	// Constructors/destructor
	HashedDictionary();
	HashedDictionary(size_t);
	~HashedDictionary();

	void clear(); // Clear the hashed dictionary
	bool isEmpty() const; // Checks if the dictionary is empty
	size_t getNumberOfItems() const; // Returns the number of items
	size_t getSize(); // Returns the size
	int getLoadFactor(); // Returns the efficiency

	// Mutators
	bool add(const KeyType &, const ItemType &);
	bool remove(const KeyType &);

	ItemType getItem(const KeyType &); // Get the item at a particular key
	bool contains(const KeyType &); // Checks if an item with a certain key exists
	void traverse(void visit(const ItemType &)); // Traverses the dictionary
	void traverseIndex(void visit(const ItemType &), size_t); // Traverses the dictionary at an index
};

template <typename KeyType, typename ItemType>
const size_t HashedDictionary<KeyType, ItemType>::DEFAULT_SIZE = 53;

// Default constructor
template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary() :
	itemCount(0), hashTableSize(DEFAULT_SIZE) {
	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];

	// Intialize each member of the array to nullptr
	for (size_t i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

// Constructor with specified size
template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(size_t hts) :
	itemCount(0), hashTableSize(hts) {
	// Check that the specified size is prime
	if (!isPrime(hts))
		throw "Hash table size isn't prime!";

	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];

	// Intialize each member of the array to nullptr
	for (size_t i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

// Destructor
template <typename KeyType, typename ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary() {
	clear();

	delete[] hashTable;
	hashTable = nullptr;
}

template <typename KeyType, typename ItemType>
void HashedDictionary<KeyType, ItemType>::clear() {
	// Traverse the array
	for (size_t i = 0; i < hashTableSize; i++) {
		HashedEntry<KeyType, ItemType> *pCur = hashTable[i];
		HashedEntry<KeyType, ItemType> *pNext;

		// Traverse the linked list, and delete each member
		while (pCur != nullptr) {
			pNext = pCur->getNext();
			delete pCur;
			pCur = pNext;
		}

		hashTable[i] = nullptr;
	}

	// Reset the item count
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

/*
Hash a search key by:
- Repeatedly bitwise right shifting by 16
- Using bitwise XOR on the shifted search key with the unshifted search key
- Multiplying by 0x45d9f3b = 73244475
- Taking the mod of the seach key with the hash table size
*/
template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getHashIndex(const unsigned int &searchKey) const {
	searchKey = ((searchKey >> 16) ^ searchKey) * 0x45d9f3b;
	searchKey = ((searchKey >> 16) ^ searchKey) * 0x45d9f3b;
	searchKey = (searchKey >> 16) ^ searchKey;

	return searchKey % hashTableSize;
}

/*
Initialize an unsigned long to 5381 (a prime number).
For each character in the searchKey string, add the hash value to itself
shifted 5 bits to the left, then add the ASCII value of the character.
Take the modulus of the hash value with the size of the hash table.
*/
template <typename KeyType, typename ItemType>
size_t HashedDictionary<KeyType, ItemType>::getHashIndex(const std::string &searchKey) const {
	unsigned long hash = 5381;

	for (size_t i = 0; i < searchKey.length(); i++)
		hash = ((hash << 5) + hash) + searchKey[i];

	return hash % hashTableSize;
}

/*
Loop a counter variable from 2 to the square root of the number, and check if the number is divisible by
the counter variable.
If so, the number isn't prime. If not, the number is prime.
*/
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

	// Hash the search key
	size_t itemHashIndex = getHashIndex(searchKey);
	loadFactor++;

	// If there aren't any items with the hash index
	if (hashTable[itemHashIndex] == nullptr) {
		hashTable[itemHashIndex] = pEntryToAdd;
		loadFactor++;
	}
	// If there already exist items with the same hash index
	else {
		// Add the new item to the beginning of the linked list
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

	// Hash the search key
	size_t itemHashIndex = getHashIndex(searchKey);

	if (hashTable[itemHashIndex] != nullptr) {
		// If the item happens to be the first in the linked list
		if (searchKey == hashTable[itemHashIndex]->getKey()) {
			// Remove the item from the linked list
			HashedEntry<KeyType, ItemType> *pEntryToRemove = hashTable[itemHashIndex];
			hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
			delete pEntryToRemove;
			pEntryToRemove = nullptr;
			itemFound = true;
		}
		else {
			HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
			HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();

			// Traverse the linked list until the item is found
			while (pCurr != nullptr && !itemFound) {
				if (searchKey == pCurr->getKey()) {
					// When the item is found, remove it from the linked list
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
	// Hash the search key
	size_t itemHashIndex = getHashIndex(searchKey);

	// Make sure the item exists
	if (hashTable[itemHashIndex] != nullptr) {
		// If the item happens to be the first in the linked list
		if (searchKey == hashTable[itemHashIndex]->getKey())
			return hashTable[itemHashIndex]->getItem();

		HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
		HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();
		
		// Traverse through the linked list
		while (pCurr != nullptr) {
			// If the item was found
			if (searchKey == pCurr->getKey()) {
				// Move the item to the front of the linked list and return it
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
	// Hash the search key
	size_t itemHashIndex = getHashIndex(searchKey);

	// Make sure the item exists
	if (hashTable[itemHashIndex] != nullptr) {
		// If the item happens to be the first in the linked list
		if (searchKey == hashTable[itemHashIndex]->getKey())
			return true;

		HashedEntry<KeyType, ItemType> *pPrev = hashTable[itemHashIndex];
		HashedEntry<KeyType, ItemType> *pCurr = pPrev->getNext();

		// Traverse through the linked list
		while (pCurr != nullptr) {
			// If the item was found
			if (searchKey == pCurr->getKey()) {
				// Move the item to the front of the linked list and return true
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
	// Traverse through the array
	for (size_t i = 0; i < hashTableSize; i++) {
		HashedEntry<KeyType, ItemType> *pCurr = hashTable[i];

		// Traverse through the linked list
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
	// Make sure the index is within range
	if (i >= hashTableSize) {
		throw HashedDictionary<KeyType, ItemType>::OutOfRangeException();
	}
	HashedEntry<KeyType, ItemType> *pCurr = hashTable[i];

	// Traverse through the linked list at that index
	while (pCurr != nullptr) {
		visit(pCurr->getItem());
		pCurr = pCurr->getNext();
	}
}