// 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


template <typename T>
class LListNode
{
public:
	LListNode(const T& t) : _t(t), _next(0) {}
	void RemoveAll()
	{
		if (_next)
		{
			_next->RemoveAll();
			_next = NULL;
		}
		delete this;
	}
	T _t;
	LListNode<T>* _next;
	void AddToTail(LListNode<T>* node)
	{
		if (_next)
			_next->AddToTail(node);
		else
			_next = node;

	}
};

template <typename T>
class Stack
{
	LListNode<T>* listHead;
public:
	Stack() : listHead(0) {}
	~Stack() { if (listHead) listHead->RemoveAll(); }
	void push(T t)
	{
		LListNode<T>* node = new LListNode<T>(t);
		node->_next = listHead;
		listHead = node;
	}
	T pop()
	{
		if (!listHead)
			return 0;

		T t = listHead->_t;
		LListNode<T>* node = listHead->_next;
		delete listHead;
		listHead = node;
		return t;
	}
};

template <typename T>
class Queue
{
	LListNode<T>* listHead;
	LListNode<T>* listTail;
public:
	Queue() : listHead(0), listTail(0) {}
	~Queue() { if (listHead) listHead->RemoveAll(); }
	void enqueue(T t)
	{
		if (!listHead)
			listHead = listTail = new LListNode<T>(t);
		else
		{
			listTail->_next = new LListNode<T>(t);
			listTail = listTail->_next;
		}			
	}
	T dequeue()
	{
		if (!listHead)
			return 0;

		T t = listHead->_t;
		
		LListNode<T>* node = listHead->_next;
		delete listHead;
		listHead = node;
		
		return t;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

