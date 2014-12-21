/*
 * MyHashMap.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: itayabu
 */

#include "MyLinkedList.h"
#include <iostream>
#include "MyHashMap.h"
#define EPSILON 0.001

/**
 * hash function for strings
 */
int MyHashMap::myHashFunction(const std::string &str)
{
	int sum = 0;
	int i = 0;
	while(str[i] != '\0')
	{
		sum += (int)str[i];
		i ++;
	}
	return sum % HASH_SIZE;
}


/**
 * Class constructor
 */
MyHashMap::MyHashMap()
{
	_size = 0;
}

/**
 * Class destructor
 */
MyHashMap::~MyHashMap()
{
}

/**
 * add a string to the HashMap. Locate the entry of the relevant linked list in
 * the HashMap using the function myHashFunction, and add the element to the end of that list.
 * If the element already exists in the HashMap, change its data to the
 * input parameter. Important: unlike our MyLinkedList, that HashMap will contain at most
 * one copy of each std::string.
 * complexity: hash (1) remove from list is as long as the list is (k), add to list (1): O(k)
 */
void MyHashMap::add(const std::string &str, double data)
{
	int hashPalce = myHashFunction(str);
	if(_hashT[hashPalce].remove(str) > 0)
	{
		_size --;
	}
	_hashT[hashPalce].add (str, data);
	_size ++;
}

/**
 * remove a string from the HashMap. Locate the entry of the relevant linked list in
 * the HashMap using the function myHashFunction, and remove the element from it.
 * Return one on success, or zero if the element wasn't in the HashMap.
 * complexity: hash (1) remove from list is as long as the list is (k): O(k)
 */
size_t MyHashMap::remove(const std::string &str)
{
	if (_hashT[myHashFunction(str)].remove(str) > 0)
	{
		_size --;
		return 1;
	}
	return 0;
}

/**
 * Return true if the element is in the HashMap, or false otherwise.
 * If the element exists in the hash map, return in 'data' its appropriate data
 * value. Otherwise don't change the value of 'data'.
 * complexity: hash (1), check in list is as long as the list is (k): O(k)
 */
bool MyHashMap::isInHashMap(const std::string &str, double &data) const
{
	return _hashT[myHashFunction(str)].isInList(str, data);
}

/**
 * Return number of elements stored in the HashMap
 * complexity: has it as a field: O(1)
 */
int MyHashMap::size() const
{
	return _size;
}

/**
 * Return true if and only if there exists a string that belong both to the
 * HashMap h1 and to this HashMap
 * complexity: iterate over HASH_SIZE(h) and every node in list (k) and check if intersect
 * with h1 relative list (p): O(h*k*p)
 */
bool MyHashMap::isIntersect(const MyHashMap &h1) const
{
	for (int i = 0; i<HASH_SIZE; i++)
	{
		MyLinkedList::MyLinkedListIterator* iter = _hashT[i].getIterator();
		double a = 0;
		double& doubleref = a;
		while (iter->hasNext())
		{
			if(h1.isInHashMap(iter->nextKey(), doubleref))
			{
				delete(iter);
				return true;
			}
			else
			{
				iter->next();
			}
		}
		delete(iter);
	}
	return false;
}

/**
 * Return the total weight of the hash elements
 * complexity: iterate over HASH_SIZE(h) and go through every node in list(k)
 * O(h*k)
 */
double MyHashMap::totWeight() const
{
	double sum = 0;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		sum += _hashT[i].sumList();
	}
	return sum;
}

/**
 * copy constructor.
 * complexity: iterate over HASH_SIZE(h) and go through every node in list(k)
 * O(h*k);
 */
MyHashMap::	MyHashMap(const MyHashMap& other)
{
	for (int i = 0; i<HASH_SIZE; i++)
	{
		_hashT[i] = MyLinkedList(other._hashT[i]);
	}

	_size = other._size;
}

/**
 * operator == check if current map has same weight like other map
 * weight is measured with totWeight summing all data in all nodes.
 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
 * O(h1k1 +h2k2).
 */
bool MyHashMap::operator== (const MyHashMap& other)
{
	if ((this->totWeight() - other.totWeight() < EPSILON) &&
		((this->totWeight() - other.totWeight()) > (-EPSILON)))
	{
		return true;
	}
	return false;
}
/**
 * operator < check if current map is smaller than other map
 * weight is measured with totWeight summing all data in all nodes.
 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
 * O(h1k1 +h2k2).
 */
bool MyHashMap::operator< (const MyHashMap& other)
{
	return ((other.totWeight() - this->totWeight()) > EPSILON);
}

/**
 * operator > check if current map is bigger than other map
 * weight is measured with totWeight summing all data in all nodes.
 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
 * O(h1k1 +h2k2).
 */
bool MyHashMap::operator> (const MyHashMap& other)
{
	return ((this->totWeight() - other.totWeight()) > EPSILON);
}

/**
 * operator - return all the elements in a that are not intersect with.
 * complexity: iterate once on all elements in a (m) and check if they intersect in relative
 * lists in b (k): O(m*k);
 */
MyHashMap MyHashMap::operator- (const MyHashMap& other)
{
	MyHashMap newMap;
	std::string nodeKey;
	double nodeData;
	double unimportantDouble = 0;
	double& doubleref = unimportantDouble;


	for (int i = 0; i < HASH_SIZE; i++)
	{
		MyLinkedList::MyLinkedListIterator* iter = _hashT[i].getIterator();
		while (iter->hasNext())
		{
			nodeKey = iter->nextKey();
			nodeData = iter->nextData();
			iter->next();
			if(other.isInHashMap(nodeKey, doubleref))
			{
				continue;
			}
			else
			{
				newMap._hashT[i].add(nodeKey, nodeData);
			}
		}
		delete (iter);
	}
	return newMap;
}

/**
 * operator | is union on sets, a|b is all the elements in a and all the elements in b
 * that are not in a, meaning an element in a will stay in a|b
 * complexity: iterating once on all elements in a (m) and than  iterating on all elements in b(n)
 * and checking relative list (k) meaning O(m+n*k).
 */
MyHashMap MyHashMap::operator| (const MyHashMap& other)
{
	MyHashMap newMap;
	std::string nodeKey;
	std::string otherNodeKey;
	double unimportantDouble = 0;
	double& doubleref = unimportantDouble;

	for (int i = 0; i < HASH_SIZE; i++)
	{
		MyLinkedList::MyLinkedListIterator* iter = _hashT[i].getIterator();
		while (iter->hasNext())
		{
			nodeKey = iter->nextKey();
			newMap._hashT[i].add(nodeKey, iter->nextData());
			iter->next();
		}
		MyLinkedList::MyLinkedListIterator* otherIter = other._hashT[i].getIterator();
		while (otherIter->hasNext())
		{
			otherNodeKey = otherIter->nextKey();
			if(! (newMap.isInHashMap(otherNodeKey, doubleref)))
			{
				newMap._hashT[i].add(otherNodeKey, otherIter->nextData());
			}
			otherIter->next();
		}
		delete(iter);
		delete (otherIter);
	}
	return newMap;
}

/**
 * operation &- intersections. return all elements that are both in current and othe maps
 * complexity: iterate on m lists, on each node we check isIntersect (k nodes in list) O(m*n*k)
 */
MyHashMap MyHashMap::operator& (const MyHashMap& other)
{
	MyHashMap newMap;
	std::string nodeKey;
	double unimportantDouble = 0;
	double& doubleref = unimportantDouble;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		MyLinkedList::MyLinkedListIterator* iter = _hashT[i].getIterator();
		while (iter->hasNext())
		{
			nodeKey = iter->nextKey();
			if(other.isInHashMap(nodeKey, doubleref))
			{
				newMap._hashT[i].add(nodeKey, iter->nextData());
			}
			iter->next();
		}
		delete(iter);
	}
	return newMap;
}

/**
 * print the hashMap by rows
 * complexity: m lists, n nodes in list O(m*n)
 */
void MyHashMap::printMap() const
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		std::cout << "row " << i << std:: endl;
		_hashT[i].printList();
	}
}
