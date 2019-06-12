#include "Node.h"

template <class ItemType> Node<ItemType>::Node() 
{
	pNext = nullptr;
}

template <class ItemType> Node<ItemType>::Node(const ItemType &item) {
	data = item;
	pNext = nullptr;
}

template <class ItemType> Node<ItemType>::Node(const ItemType &item, Node<ItemType>* next) {
	data = item;
	pNext = next;
}

template <class ItemType> Node<ItemType>::Node(const Node<ItemType> &n) {
	data = n.data;
	if (n.pNext != nullptr) {
		pNext = new Node(n.pNext);
	}
}

template <class ItemType> void Node<ItemType>::setData(const ItemType &item) {
	data = item;
}

template <class ItemType> void Node<ItemType>::setNext(Node<ItemType> *next) {
	pNext = next;
}

template <class ItemType> ItemType Node<ItemType>::getData() {
	return data;
}

template <class ItemType> Node<ItemType>* Node<ItemType>::getNext() {
	return pNext;
}

template <typename T> bool operator==(Node<T> &a, Node<T>&b) {
	if (a.data != b.data) {
		return false;
	}

	if ((a.pNext == nullptr) && (b.pNext == nullptr)) {
		return true;
	}
	else if ((a.pNext == nullptr) || (b.pNext == nullptr)) {
		return false;
	}
	else {
		return *(a.pNext) == *(b.pNext);
	}
}