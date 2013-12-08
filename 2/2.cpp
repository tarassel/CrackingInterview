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
#include <stack>

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

template <typename T>
LListNode<T>* AddListsReversed(LListNode<T>* l1, LListNode<T>* l2, bool bNewLevel = false)
{
	T nNewVal = 0;
	LListNode<T>* l1next = NULL;
	LListNode<T>* l2next = NULL;

	if (!l1 && !l2)
	{
		if (bNewLevel)
			nNewVal = 0;
		else
			return NULL;
	}
	else if (!l1 || !l2)
	{
		if (l2)
		{
			nNewVal = l2->_t;
			l1next = NULL;
			l2next = l2->_next;
		}
		else
		{
			nNewVal = l1->_t;
			l1next = l1->_next;
			l2next = NULL;
		}
	}
	else
	{
		nNewVal = l1->_t + l2->_t;
		l1next = l1->_next;
		l2next = l2->_next;
	}

	if (bNewLevel)
		++nNewVal;

	LListNode<T>* pNewNode = new LListNode<T>(nNewVal % 10);
	pNewNode->_next = AddListsReversed(l1next, l2next, nNewVal >= 10);

	return pNewNode;
}

template <typename T>
int MakeListsLenEqual(LListNode<T>** l1, LListNode<T>** l2)
{
	LListNode<T>* l = NULL;

	int nLen1 = 0;
	l = *l1;
	while (l->_next)
		++nLen1, l = l->_next;
	
	int nLen2 = 0;
	l = *l2;
	while (l->_next)
		++nLen2, l = l->_next;

	LListNode<T>* lstr = NULL;
	LListNode<T>* lend = NULL;

	if (nLen1 == nLen2)
		return nLen1;
	else if (nLen1 < nLen2)
	{
		for (int i=0; i<nLen2-nLen1; ++i)
		{
			if (!lstr)
			{
				lstr = new LListNode<T>(0);
				lend = lstr;
			}
			else
			{
				lend->_next = new LListNode<T>(0);
				lend = lend->_next;
			}
		}

		lend->_next = *l1;
		*l1 = lstr;
		return nLen2;
	}
	else// if (nLen1 > nLen2)
	{
		for (int i=0; i<nLen1-nLen2; ++i)
		{
			if (!lstr)
			{
				lstr = new LListNode<T>(0);
				lend = lstr;
			}
			else
			{
				lend->_next = new LListNode<T>(0);
				lend = lend->_next;
			}
		}

		lend->_next = *l2;
		*l2 = lstr;
		return nLen1;
	}
}

template <typename T>
T GetListItemVal(LListNode<T>* l, int nPos)
{
	while (nPos > 0)
	{
		l = l->_next;
		--nPos;
	}

	return l->_t;
}

template <typename T>
LListNode<T>* AddListsIntern(LListNode<T>* l1, LListNode<T>* l2, int nPos, bool bNewLevel = false)
{
	if (nPos < 0)
	{
		if (bNewLevel)
			return new LListNode<T>(1);
		else
			return new LListNode<T>(0);
	}

	T nNewVal = GetListItemVal(l1, nPos) + GetListItemVal(l2, nPos);

	if (bNewLevel)
		++nNewVal;

	if (nNewVal >= 10)
		bNewLevel = true;
	else
		bNewLevel = false;

	LListNode<T>* pNewEndNode = new LListNode<T>(nNewVal % 10);

	LListNode<T>* pPrevNodes = NULL;
	
	--nPos;
	if (nPos < 0 && bNewLevel)
		pPrevNodes = new LListNode<T>(1);
	else if (nPos < 0 && !bNewLevel)
		pPrevNodes = pNewEndNode;
	else
	{
		pPrevNodes = AddListsIntern(l1, l2, nPos, bNewLevel);
		pPrevNodes->AddToTail(pNewEndNode);
	}

	return pPrevNodes;
}

template <typename T>
LListNode<T>* AddLists(LListNode<T>* l1, LListNode<T>* l2, bool bNewLevel = false)
{
	int nLen = MakeListsLenEqual(&l1, &l2);

	return AddListsIntern(l1, l2, nLen);
}


template <typename T>
LListNode<T>* FindLoopBeginning(LListNode<T>* head)
{
	LListNode<T> *slow = head, *fast = head;

	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;

		if (slow == fast)
			break;
	}

	if (!fast || !fast->_next)
		return NULL;

	LListNode<T>* collisionPoint = slow;
	LListNode<T>* cycleRunner = collisionPoint->_next;

	while (cycleRunner != head)
	{
		if (cycleRunner == collisionPoint)
			head = head->_next;
		cycleRunner = cycleRunner->_next;
	}

	return head;
}

template <typename T>
bool isPalindrome(LListNode<T>* head)
{
	if (!head)
		return false;

	return isPalindrome1(head) && isPalindrome2(head);
}

template <typename T>
bool isPalindrome1(LListNode<T>* head)
{
	LListNode<T>* runner = head->_next;
	LListNode<T>* newListPre = new LListNode<T>(head->_t);
	LListNode<T>* newListHead = newListPre;
	int listSize = 1;

	while (runner)
	{
		newListHead = new LListNode<T>(runner->_t);
		newListHead->_next = newListPre;
		newListPre = newListHead;
		runner = runner->_next;
		++listSize;
	}

	listSize = listSize / 2;

	while (listSize)
	{
		if (head->_t != newListHead->_t)
			return false;
		head = head->_next;
		newListHead = newListHead->_next;
		--listSize;
	}

	return true;
}

template <typename T>
bool isPalindrome2(LListNode<T>* head)
{
	LListNode<T>* runner = head;
	int listSize = 0;

	// get size
	while (runner)
	{
		++listSize;
		runner = runner->_next;
	}
	bool listSizeEven = (listSize % 2 == 0);

	listSize = listSize / 2;

	// make stack
	std::stack<T> stk;
	runner = head;

	while (listSize)
	{
		stk.push(runner->_t);
		runner = runner->_next;
		--listSize;
	}

	// step if not even
	if (!listSizeEven)
		runner = runner->_next;

	// compare
	while (runner)
	{
		if (runner->_t != stk.top())
			return false;
		stk.pop();
		runner = runner->_next;
	}

	return true;
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
	ll->RemoveAll();

	LListNode<int>* l1 = new LListNode<int>(7);
	l1->AddToTail(new LListNode<int>(1));
	l1->AddToTail(new LListNode<int>(6));
	LListNode<int>* l2 = new LListNode<int>(5);
	l2->AddToTail(new LListNode<int>(9));
	l2->AddToTail(new LListNode<int>(2));

	LListNode<int>* lres = AddListsReversed(l1, l2);
	lres->RemoveAll();

	l1 = new LListNode<int>(6);
	l1->AddToTail(new LListNode<int>(1));
	l1->AddToTail(new LListNode<int>(7));
	l2 = new LListNode<int>(1);
	l2->AddToTail(new LListNode<int>(2));
	l2->AddToTail(new LListNode<int>(9));
	l2->AddToTail(new LListNode<int>(5));
 	LListNode<int>* lres1 = AddLists(l1, l2);
 	lres1->RemoveAll();

	l1 = new LListNode<int>(1);
	l1->AddToTail(new LListNode<int>(2));
	l2 = new LListNode<int>(3);
	l1->AddToTail(l2);
	l1->AddToTail(new LListNode<int>(4));
	l1->AddToTail(new LListNode<int>(5));
	l1->AddToTail(l2);
	FindLoopBeginning(l1);
//	l1->RemoveAll();

	l1 = new LListNode<int>(1);
	l1->AddToTail(new LListNode<int>(2));
	l1->AddToTail(new LListNode<int>(3));
	l1->AddToTail(new LListNode<int>(2));
	l1->AddToTail(new LListNode<int>(1));
	assert(isPalindrome(l1));
	l1->AddToTail(new LListNode<int>(1));
	assert(!isPalindrome(l1));

	return 0;
}

