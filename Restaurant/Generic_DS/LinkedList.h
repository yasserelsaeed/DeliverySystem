#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include "PriorityQueue.h"
#include "../Rest/Order.h"+

#include <iostream>
using namespace std;

template <typename T = Order>
class LinkedList
{
private:
	Node<T>* Head;
	int count;
public:
	LinkedList();
	~LinkedList();
	Node<T>* getHead();
	bool InsertEnd(T val);
	bool InsertBeg(T val);
	int GetCount();
	void Print();
	void DeleteAll();
	bool Is_exist(Node<T>* Head, T Key);
	bool DeleteNode(T value);
	bool Remove(T& val);
	T RmvFirst();
	bool Cancel(int ID);
	bool promote(int ID, PriorityQueue<T>& Q,double ExtraMoney,double Time);
	 T * toArray() ;
	 bool Peek(T&);
};

template<class T>
LinkedList<T>::LinkedList()
{
	count = 0;
	Head = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	//DeleteAll();
}

template<class T>
Node<T>* LinkedList<T>::getHead()
{
	return Head;
}

template<class T>
bool LinkedList<T>::InsertEnd(T val)
{
	Node<T>* ptr = new Node<T>(val);
	if (!ptr)return false;
	if (Head)
	{
		Node<T>* scanptr = Head;
		while (scanptr->getNext())scanptr = scanptr->getNext();
		scanptr->setNext(ptr);
	}
	else Head = ptr;
	count++;
	return true;
}

template<class T>
bool LinkedList<T>::InsertBeg(T val)
{
	Node<T>* ptr = new Node<T>(val);
	if (!ptr) return false;
	if (Head)
	{
		ptr->setNext(Head);
	}
	Head = ptr;
	count++;
	return true;
}

template<class T>
void LinkedList<T>::Print()
{
	cout << "\nThe number of nodes in the list is : " << count;
	cout << "\nThe list :\n";
	Node<T> *ptr = Head;

	while (ptr != NULL)
	{
		cout << "[ " << ptr->getItem().GetID() << " ]";
		cout << "--->";
		ptr = ptr->getNext();
	}
	cout << "*\n";
}

template<class T>
void LinkedList<T>::DeleteAll()
{
	Node<T> *P = Head;
	while (Head != NULL)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
	count = 0;
}

template<class T>
bool LinkedList<T>::Is_exist(Node<T>* Head, T Key)
{
	Node<T>* ptr = Head;
	while (ptr)
	{
		if (ptr->getItem() == Key)return true;
		ptr = ptr->getNext();
	}
	return false;
}


template<class T>
bool LinkedList<T>::DeleteNode(T value)
{
	if (count == 0)return false;
		if (Head->getItem() == value)
		{
			Node<T>* deleteptr = Head;
			Head = Head->getNext();
			delete deleteptr;
			count--;
			return true;
		}
		else
		{
			Node<T>* ptr = Head;
			while (ptr->getNext())
			{
				if ((ptr->getNext())->getItem() == value)
				{
					Node<T>* deleteNode = ptr->getNext();
					ptr->setNext(deleteNode->getNext());
					delete deleteNode;
					count--;
					return true;
				}
				ptr = ptr->getNext();
			}
		}
	
	return false;
}

template<typename T>
inline bool LinkedList<T>::Remove(T & val)
{
	if (Head)
	{
		val = Head->getItem();
		Node<T>* ptr = Head;
		Head = Head->getNext();
		count--;
		delete ptr;
		return true;
	}
	return false;
}

template<typename T>
T LinkedList<T>::RmvFirst()
{
	if (Head)
	{
		Node<T>* ptr = Head;
		Head = Head->getNext();
		count--;
		return ptr->getItem();
	}
	return NULL;
}

template <class T>
bool LinkedList<T>::Cancel(int ID)
{
	Node<T>* ptr = Head;
	while (ptr && (ptr->getItem()).GetID()!=ID)ptr=ptr->getNext();
	if (ptr)
	{
		DeleteNode(ptr->getItem());
		return true;
	}
	return false;
}
template<typename T>
bool LinkedList<T>::promote(int ID,PriorityQueue<T>& Q, double ExtraMoney,double Time)
{
	Node<T>* ptr = Head;
	if(ptr)
	{
		if (ptr->getItem().GetID() == ID)
		{
			double p = ptr->getItem().CalcPriority();
			Head = ptr->getNext();
			Q.addPromoted(ptr, p);
			return true;
		}
		while (ptr->getNext() && ptr->getNext()->getItem().GetID() != ID) { ptr = ptr->getNext(); }
		Node<T>* promo = ptr->getNext();
		ptr->setNext(promo->getNext());
		double p = promo->getItem().CalcPriority();
		Q.addPromoted(promo, p);
		return true;

	}
	return false;
}
template < class T>
 T * LinkedList<T>::toArray() 
{
	T * arr = new T[count];
	Node<T>* curPtr = Head;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < count))
	{
		arr[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	return arr;
} // end toArray

 template<class T>
int  LinkedList<T>::GetCount()
 {
	 return count;
 }

template<class T>
bool LinkedList<T>::Peek(T& ItemToPeek)
{
	if (!Head)
		return false;
	ItemToPeek = Head->getItem();
	return true;
}
#endif