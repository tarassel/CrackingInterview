// 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>

void RemoveDups1(std::list<int>& l)
{
	std::set<int> s(l.begin(), l.end());
	l.clear();
	l.assign(s.begin(), s.end());
}

void RemoveDups2(std::list<int>& l)
{
	std::map<int, bool> m;
	std::list<int>::const_iterator pos;
	for (pos = l.begin(); pos != l.end(); )
	{
		if (m[*pos] == false)
		{
			m[*pos] = true;
			++pos;
		}
		else
			pos = l.erase(pos);
	}
}

void RemoveDups3(std::list<int>& l)
{
	std::list<int>::const_iterator pos;
	for (pos = l.begin(); pos != l.end(); ++pos)
	{
		int val = *pos;
		std::list<int>::const_iterator posCurr = pos;
		for (std::list<int>::const_iterator pos2 = ++posCurr; pos2 != l.end(); )
		{
			if (val == *pos2)
				pos2 = l.erase(pos2);
			else
				++pos2;
		}
	}
}

template <typename T>
class LListNode
{
public:
	LListNode(const T& t): _t(t), _next(0) {}
	void RemoveAll() { if (_next) delete _next; delete this; }
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
void RemoveDups4(LListNode<T>& ll)
{
	LListNode<T>* current = &ll;
	while (current->_next)
	{
		LListNode<T>* iter = current;
		while (iter->_next)
		{
			if (current->_t == iter->_next->_t)
			{
				LListNode<T>* toDel = iter->_next;
				iter->_next = iter->_next->_next;
				delete toDel;
			}
			else
				iter = iter->_next;
		}
		current = current->_next;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[] = {1,1,2,3,1};
	std::list<int> l(arr, arr+5);
	std::cout << "Before RemoveDups\n";
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout << std::endl;
	RemoveDups3(l);
	std::cout << "After RemoveDups\n";
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout << std::endl;

	LListNode<int>* ll = new LListNode<int>(1);
	ll->AddToTail(new LListNode<int>(1));
	ll->AddToTail(new LListNode<int>(2));
	ll->AddToTail(new LListNode<int>(3));
	ll->AddToTail(new LListNode<int>(1));
	RemoveDups4<int>(*ll);

	ll->RemoveAll();

	return 0;
}

