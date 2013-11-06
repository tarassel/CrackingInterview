// 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <assert.h>
#include <vector>

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

// Bullshit
template <typename T>
LListNode<T>* nthToLast(LListNode<T>* ll, int k)
{
	std::vector<LListNode<T>*> arr;

	do
	{
		arr.push_back(ll);
		ll = ll->_next;
	}
	while (ll);

	if (static_cast<std::vector<LListNode<T>*>::size_type>(k) > arr.size())
		return 0;
	else
		return arr[arr.size() - k];
}

template <typename T>
LListNode<T>* nthToLast2(LListNode<T>* ll, int k)
{
	LListNode<T>* iter = ll;
	std::vector<LListNode<T>*> arr;
	int n = 1;

	while (iter->_next)
	{
		n++;
		iter = iter->_next;
	}

	if (k > n)
		return 0;
	else
	{
		for (int i=0; i<n-k; i++)
			ll = ll->_next;
		return ll;
	}
}

template <typename T>
LListNode<T>* nthToLast3(LListNode<T>* ll, int k)
{
	LListNode<T>* p1 = ll;
	LListNode<T>* p2 = ll;

	int i;
	for (i = 0; i < k && p2; i++)
		p2 = p2->_next;

	if (!p2 && i < k)
		return 0;

	while(p2)
	{
		p2 = p2->_next;
		p1 = p1->_next;
	}

	return p1;
}

// Cannot delete last elem
template <typename T>
void DeleteNode(LListNode<T>* node)
{
	if (!node || !node->_next)
		return;

	LListNode<T>* nextNode = node->_next;
	*node = *node->_next;
	delete nextNode;
}

template <typename T>
LListNode<T>* Patrition(LListNode<T>* node, int x)
{
	LListNode<T> *lesBeg = 0, *lesEnd = lesBeg, *bigBeg = 0, *bigEnd = bigBeg;
	while (node)
	{
		if (node->_t < x)
		{
			if (!lesBeg)
				lesBeg = lesEnd = node;
			else
				lesEnd = lesEnd->_next = node;
		}
		else
		{
			if (!bigBeg)
				bigBeg = bigEnd = node;
			else
				bigEnd = bigEnd->_next = node;
		}

		node = node->_next;
	}

	lesEnd->_next = bigBeg;
	bigEnd->_next = 0;

	return lesBeg;
}

template <typename T>
LListNode<T>* Patrition2(LListNode<T>* node, int x)
{
	LListNode<T> *lesBeg = 0, *bigBeg = 0;

	while (node)
	{
		LListNode<T> *next = node->_next;
		if (node->_t < x)
		{
			node->_next = lesBeg;
			lesBeg = node;
		}
		else
		{
			node->_next = bigBeg;
			bigBeg = node;
		}

		node = next;
	}

	if (!lesBeg)
		return bigBeg;

	LListNode<T> *head = lesBeg;
	while (lesBeg->_next)
		lesBeg = lesBeg->_next;
	lesBeg->_next = bigBeg;

	return head;
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
	ll->AddToTail(new LListNode<int>(4));
	ll->AddToTail(new LListNode<int>(5));
	ll->AddToTail(new LListNode<int>(1));
	RemoveDups4<int>(*ll);

	assert(nthToLast<int>(ll, 2)->_t == 4);
	assert(nthToLast<int>(ll, 1)->_t == 5);
	assert(nthToLast<int>(ll, 5)->_t == 1);
	assert(nthToLast2<int>(ll, 2)->_t == 4);
	assert(nthToLast2<int>(ll, 1)->_t == 5);
	assert(nthToLast2<int>(ll, 5)->_t == 1);
	assert(nthToLast3<int>(ll, 2)->_t == 4);
	assert(nthToLast3<int>(ll, 1)->_t == 5);
	assert(nthToLast3<int>(ll, 5)->_t == 1);

	// Del middle and first el
	DeleteNode(ll->_next);
	DeleteNode(ll);

	ll->RemoveAll();


	ll = new LListNode<int>(1);
	ll->AddToTail(new LListNode<int>(1));
	ll->AddToTail(new LListNode<int>(2));
	ll->AddToTail(new LListNode<int>(3));
	ll->AddToTail(new LListNode<int>(4));
	ll->AddToTail(new LListNode<int>(5));
	ll->AddToTail(new LListNode<int>(1));
	LListNode<int>* res = Patrition2(ll, 3);

	return 0;
}

