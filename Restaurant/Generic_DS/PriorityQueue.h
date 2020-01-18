#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "..\pNode.h"
#include <iostream>
using namespace std;

template <typename T>
class PriorityQueue
{
private:

	pNode<T>* backPtr;
	pNode<T>* frontPtr;
	int count;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, double p);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	int GetCount() const;
	void Print();
	bool addPromoted(T& N, double p);
	~PriorityQueue();
};

template <class T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = frontPtr = NULL;
	count = 0;
}

template <class T>
bool PriorityQueue<T>::isEmpty()const
{
	if (frontPtr == NULL)return true;
	return false;
}

template <class T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double p)
{

	pNode<T>* ptr = new pNode<T>(newEntry, p);
	if (ptr)
	{
		if (isEmpty())
		{
			frontPtr = backPtr = ptr;
		}
		else
		{
			if (frontPtr->getPriority() < p)

			{
				ptr->setNext(frontPtr);
				frontPtr = ptr;
			}
			else
			{
				pNode<T>* scanptr = frontPtr;
				while (scanptr->getNext() && (scanptr->getNext()->getPriority() >= p))
				{
					scanptr = scanptr->getNext();
				}
				ptr->setNext(scanptr->getNext());
				scanptr->setNext(ptr);
			}
		}
		count++;
		return true;
	}
	return false;
}

template<class T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (frontPtr)
	{
		pNode<T>* ptr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		delete ptr;
		count--;
		return true;
	}
	return false;
}

template<class T>
bool PriorityQueue<T>::peekFront(T& frntEntry)  const
{
	if (frontPtr)
	{
		frntEntry = frontPtr->getItem();
		return true;
	}
	return false;
}

template<typename T>
inline int PriorityQueue<T>::GetCount() const
{
	return count;
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
	//T x;
	//while (dequeue(x));
}

template<class T>
void PriorityQueue<T>::Print()
{
	cout << "\nThe Queue :\n";
	pNode<T> *ptr = frontPtr;

	while (ptr != NULL)
	{
		cout << "[ " << ptr->getItem().GetID() << " ]";
		cout << "--->";
		ptr = ptr->getNext();
	}
	cout << "*\n";
}
template<typename T>
bool PriorityQueue<T>::addPromoted(T& N, double p)
{
	pNode<T>* pN = new pNode<T>(N,p);
	if (pN)
	{
		if (isEmpty())
		{
			frontPtr = backPtr = N;
		}
		else
		{
			if (frontPtr->getPriority() < p)

			{
				N->setNext(frontPtr);
				frontPtr = N;
			}
			else
			{
				pNode<T>* scanptr = frontPtr;
				while (scanptr->getNext() && (scanptr->getNext()->getPriority() >= p))
				{
					scanptr = scanptr->getNext();
				}
				N->setNext(scanptr->getNext());
				scanptr->setNext(N);
			}
		}
		return true;
	}
	return false;
}
#endif
