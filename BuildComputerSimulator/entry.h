#pragma once

template <typename KeyType, typename ItemType>
class Entry {
private:
	KeyType searchKey;
	ItemType item;

protected:
	void setKey(const KeyType &);

public:
	Entry();
	Entry(KeyType, ItemType);

	KeyType getKey() const;
	ItemType getItem() const;
	void setItem(const ItemType &);

	bool operator ==(const Entry<KeyType, ItemType> &) const;
	bool operator >(const Entry<KeyType, ItemType> &) const;
};

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry() {}

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry(KeyType sk, ItemType i) : searchKey(sk), item(i) {}

template <typename KeyType, typename ItemType>
KeyType Entry<KeyType, ItemType>::getKey() const {
	return searchKey;
}

template <typename KeyType, typename ItemType>
ItemType Entry<KeyType, ItemType>::getItem() const {
	return item;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setKey(const KeyType &sk) {
	searchKey = sk;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setItem(const ItemType &i) {
	item = i;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator ==(const Entry<KeyType, ItemType> &rightHandItem) const {
	return searchKey == rightHandItem.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator >(const Entry<KeyType, ItemType> &rightHandItem) const {
	return searchKey > rightHandItem.searchKey;
}