#pragma once

#ifndef P_NODE_H_
#define P_NODE_H_

template < typename T>
class pNode
{
private:
	T item;					// A data item
	pNode<T>* next;			// Pointer to next node

	double priority;
public:
	pNode();
	pNode(const T & r_Item, double p = 0);	//passing by const ref.
	pNode(const T & r_Item, pNode<T>* nextNodePtr, double p = 0);

	void setItem(const T & r_Item);
	void setNext(pNode<T>* nextNodePtr);
	T getItem() const;
	pNode<T>* getNext() const;
	double getPriority()const;
	void setPriority(const T & p);
}; // end Node


template < typename T>
pNode<T>::pNode()
{
	next = nullptr;
	priority = 0;
}

template < typename T>
pNode<T>::pNode(const T& r_Item, double p)
{
	item = r_Item;
	next = nullptr;
	priority = p;
}

template < typename T>
pNode<T>::pNode(const T& r_Item, pNode<T>* nextNodePtr, double p)
{
	item = r_Item;
	next = nextNodePtr;
	priority = p;
}
template < typename T>
void pNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void pNode<T>::setNext(pNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T pNode<T>::getItem() const
{
	return item;
}

template <typename T>
double pNode<T>::getPriority()const
{
	return priority;
}

template < typename T>
pNode<T>* pNode<T>::getNext() const
{
	return next;
}

template <typename T>
void pNode<T>::setPriority(const T& p)
{
	priority = p;
}
#endif