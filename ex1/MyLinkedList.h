/*
 * MyLinkedList.h
 *
 *  Created on: Aug 24, 2014
 *      Author: itayabu
 */

#ifndef MYLINKEDLIST_H_
#define MYLINKEDLIST_H_
#include <iostream>



/**
 * linked list class.
 * two way list that hold nodes contain string key and double data
 */
class MyLinkedList
{
private:
	/**
	 * simple node class for MyLinkedList.
	 * contain key, data and pointers to next and prev nodes.
	 */
class MyLinkedListNode;
	/**
	 * delete a node, connect the list on both sides
	 */
	void _deleteNode(MyLinkedListNode* currentNode);

public:

	/**
	 * iterator class for MyLinkedList.
	 * go through all nodes in list, return nextData and nextKey
	 */
	class MyLinkedListIterator
	{
		private:
			double _nextData;
			std::string _nextKey;
			MyLinkedListNode* _iterNode;

			/**
			 * update current key and data
			 */
			 void _updateIter();
		public:

			 /**
			  * basic constructor, receive a list to iterate upon.
			  */
			MyLinkedListIterator(MyLinkedList list);

			/**
			 * return true iff current node is not empty
			 */
			bool hasNext();

			/**
			 * advances the iterator
			 */
			void next();

			/**
			 * return current data
			 */
			double nextData();

			/**
			 * return current key
			 */
			std::string nextKey();
	};
	/**
	 * pointers to first and last nodes
	 */
	MyLinkedListNode *_first, *_last;
	/**
	 * simple constructor
	 */
	MyLinkedList();
	/**
	 * copy constructor
	 */
	MyLinkedList(const MyLinkedList& other);
	/**
	 * class destructor
	 */
	virtual ~MyLinkedList();
	/**
	 * add a new node to list
	 */
	void add( std::string key, double value);
	/**
	 * remove all nodes with current key as their key
	 */
	int remove (std::string deleteKey);
	/**
	 * this method check if a node containing a given key is in list,
	 * if node exist, method return true and change the given reference the node's value
	 * else, return false
	 */
	bool isInList(std::string key, double& ref) const;
	/**
	 * method print list of all nodes.
	 * if list is empty, method print Empty, if not,
	 * method print every node's key and value
	 */
	void printList () const;
	/**
	 * this method calculate the sum of all node in list.
	 */
	double sumList() const;

	/**
	 * operator = for linked list
	 */
	MyLinkedList& operator=(const MyLinkedList&);

	/**
	 * return an iterator of current list
	 */
	MyLinkedListIterator* getIterator()const;
};

#endif /* MYLINKEDLIST_H_ */
