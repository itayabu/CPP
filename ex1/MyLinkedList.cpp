/*
 * MyLinkedList.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: itayabu
 */

#include "MyLinkedList.h"
#include <iostream>

/**
 * simple node fir linked list.
 */
class MyLinkedList::MyLinkedListNode
{
public:
	double _data;
	std::string _key;
	MyLinkedListNode *_next, *_prev;
	MyLinkedListNode(std::string key, double data)
	{
		_key = key;
		_data = data;
		_next = NULL;
		_prev = NULL;
	}
};

/**
 * simple constructor
 */
MyLinkedList::MyLinkedList()
{
	_first = NULL;
	_last = NULL;
}

/**
 * copy constructor
 */
MyLinkedList::MyLinkedList(const MyLinkedList& other)
{
	this->_last = this->_first = NULL;
	for(MyLinkedListNode* p = other._first ; p != NULL ; p = p->_next)
	{
		this->add(p->_key , p->_data);
	}
}


/**
 * add a new node to list
 */
void MyLinkedList:: add(std::string key, double value)
{
	if (_first == NULL)
	{
		_first = new MyLinkedListNode(key, value);
		_last = _first;
	}
	else
	{
		MyLinkedListNode *newNode = new MyLinkedListNode(key, value);
		newNode->_prev = _last;
		_last->_next = newNode;
		_last = newNode;
	}
}

/**
 * delete a node, connect the list on both sides
 */
void MyLinkedList::_deleteNode(MyLinkedListNode* currentNode)
{
	if (!(currentNode->_next == NULL && currentNode->_prev == NULL))
	{
		if (currentNode->_next != NULL)
		{
			currentNode->_next->_prev = currentNode->_prev;
		}
		if (currentNode->_prev != NULL)
		{
			currentNode->_prev->_next = currentNode->_next;
		}
	}
	else
	{
		_first = NULL;
		_last = NULL;

	}
	delete(currentNode);
}

/**
 * remove all nodes with current key as their key
 */
int MyLinkedList::remove (std::string deleteKey)
{
	int numOfDeleted = 0;
	if (_first == NULL)
	{
		return 0;
	}
	MyLinkedListNode* currentNode = _first;

	//check all nodes except the first
	while(currentNode->_next != NULL)
	{
		if (currentNode->_next->_key.compare(deleteKey) == 0)
		{
			_deleteNode(currentNode->_next);
			numOfDeleted++;

		}
		else
		{
			if(currentNode->_next != NULL)
			{
				currentNode = currentNode->_next;
			}
		}
	}
	_last = currentNode;

	//	handle case where first node needs to delete
	if (_first->_key.compare(deleteKey) == 0)
	{
		numOfDeleted++;
		if (_first != _last)
		{
			_first = _first->_next;

		}
		_deleteNode(currentNode);
	}
	return numOfDeleted;
}

/**
 * this method check if a node containing a given key is in list,
 * if node exist, method return true and change the given reference the node's value
 * else, return false
 */
bool MyLinkedList::isInList(std::string key, double& ref)const
{
	MyLinkedListNode * currentNode = _first;
	while (!(currentNode == NULL))
	{
		if (currentNode->_key.compare(key) == 0)
		{
			ref = currentNode->_data;
			return true;
		}
		currentNode = currentNode->_next;
	}
	return false;
}

/**
 * method print list of all nodes.
 * if list is empty, method print Empty, if not,
 * method print every node's key and value
 */
void MyLinkedList::printList() const
{
	if (_first == NULL)
	{
		std::cout << "Empty\n";
	}
	else
	{
		MyLinkedListNode* currentNode = _first;
		while (currentNode!=NULL)
		{
			std::cout << currentNode->_key << "," << currentNode->_data << "\n";
			currentNode = currentNode->_next;
		}
	}
}

/**
 * this method calculate the sum of all node in list.
 */
double MyLinkedList::sumList()const
{
	double sum = 0;
	MyLinkedListNode* cusrrentNode = _first;
	while (cusrrentNode != NULL)
	{
		sum += cusrrentNode->_data;
		cusrrentNode = cusrrentNode->_next;
	}
	return sum;
}
/**
 * class destructor
 */
MyLinkedList::~MyLinkedList()
{
	if (_first == NULL)
	{
		_last = NULL;
	}
	else
	{
		while (_first->_next != NULL)
		{
			_deleteNode(_first->_next);
		}
		_deleteNode(_first);
	}
}


/**
 * operator = for linked list
 */
MyLinkedList& MyLinkedList::operator=(const MyLinkedList& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->~MyLinkedList();
	for(MyLinkedListNode *p = other._first ; p != NULL ; p = p->_next)
	{
		this->add(p->_key , p->_data);
	}
	return *this;
}

/**
 * advances the iterator
 */
void MyLinkedList::MyLinkedListIterator::next()
{
	_iterNode = _iterNode->_next;
	_updateIter();
	return;
}

/**
 * update current key and data
 */
void  MyLinkedList::MyLinkedListIterator::_updateIter()
{
	if (_iterNode != NULL)
	{
		_nextData = _iterNode->_data;
		_nextKey = _iterNode->_key;
	}
}

/**
 * basic constructor, receive a list to iterate upon.
 */
MyLinkedList::MyLinkedListIterator::MyLinkedListIterator(MyLinkedList list)
{
	_iterNode = list._first;
	_nextData = 0;
	_nextKey = "\0";
	if (_iterNode != NULL)
	{
		std::string a = list._first->_key;
		_nextData = list._first->_data;
		_nextKey = list._first->_key;
	}
}

/**
 * return true iff current node is not empty
 */
bool MyLinkedList::MyLinkedListIterator::hasNext()
{
	return (!(_iterNode == NULL));
}

/**
 * return an iterator of current list
 */
MyLinkedList::MyLinkedListIterator* MyLinkedList::getIterator()const
{

	return new MyLinkedListIterator(*this);
}

/**
 * return current data
 */
double MyLinkedList::MyLinkedListIterator::nextData()
{
	return _nextData;
}

/**
 * return current key
 */
std::string MyLinkedList::MyLinkedListIterator:: nextKey()
{
	return _nextKey;
}








