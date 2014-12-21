/**
 * MyHashMap.h
 *
 * --------------------------------------------------------------------------------------
 * General: This class represents a Hashmap, a data structure that provide fast accession to
 *          data stored in.
 *          Depend on MyLinkedList
 *
 *  Methods: MyHashMap() - Constructor
 *  ~MyHashMap()         - Destructor
 *
 *  add                  - Add a string to the HashMap. Locate the entry of the relevant linked list in
 *                         the HashMap using the function myHashFunction, and add the element to
 *                         the end of that list.
 *                         If the element already exists in the HashMap, change its data to the
 *                         input parameter. Important: unlike our MyLinkedList, this HashMap will
 *                         contain at most one copy of each std::string.
 *
 *  remove               - Remove a string from the HashMap. Locate the entry of the relevant linked
 *                         list in the HashMap using the function myHashFunction, and remove the element
 *                         from it.
 *                         Return true on success, or false if the element wasn't in the HashMap.
 *
 *  isInHashMap            - Return true if the element is in the HashMap, or false otherwise.
 *                         If the element exists in the HashMap, return in 'data' its appropriate data
 *                         value. Otherwise don't change the value of 'data'.
 *
 *  size                 - Return number of elements stored in the HashMap.
 *
 *  isIntersect            - Return true if and only if there exists a string that belongs both to the
 *                         HashMap h1 and to this HashMap
 *
 *  totWeight            - Return the total weight of the hash elements
 *
 * --------------------------------------------------------------------------------------
 */
#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <string>
#include "MyLinkedList.h"
#define HASH_SIZE 29	 // The number of entrances of the hash table
						 // should be a prim number

/**
 * The definition of the HashMap
 */
class MyHashMap
{
public:
	/**
	 * The hash function.
	 */
	static int myHashFunction(const std::string &str);

	/**
	 * Class constructor
	 */
	MyHashMap();

	/**
	 * Class destructor
	 */
	~MyHashMap();

	/**
	 * add a string to the HashMap. Locate the entry of the relevant linked list in
	 * the HashMap using the function myHashFunction, and add the element to the end of that list.
	 * If the element already exists in the HashMap, change its data to the
	 * input parameter. Important: unlike our MyLinkedList, that HashMap will contain at most
	 * one copy of each std::string.
	 * complexity: hash (1) remove from list is as long as the list is (k), add to list (1): O(k)
	 */
	void add(const std::string &str, double data);
	
	/**
	 * remove a string from the HashMap. Locate the entry of the relevant linked list in
	 * the HashMap using the function myHashFunction, and remove the element from it.
	 * Return one on success, or zero if the element wasn't in the HashMap.
	 * complexity: hash (1) remove from list is as long as the list is (k): O(k)
	 */
	size_t remove(const std::string &str);
	
	/**
	 * Return true if the element is in the HashMap, or false otherwise.
	 * If the element exists in the hash map, return in 'data' its appropriate data
	 * value. Otherwise don't change the value of 'data'.
	 * complexity: hash (1), check in list is as long as the list is (k): O(k)
	 */
	bool isInHashMap(const std::string &str, double &data) const;
	
	/**
	 * Return number of elements stored in the HashMap
	 * complexity: has it as a field: O(1)
	 */
	int size() const;
	
	/**
	 * Return true if and only if there exists a string that belong both to the
	 * HashMap h1 and to this HashMap
	 * complexity: iterate over HASH_SIZE(h) and every node in list (k) and check if intersect
	 * with h1 relative list (p): O(h*k*p)
	 */
	bool isIntersect(const MyHashMap &h1) const;
	
	/**
	 * Return the total weight of the hash elements
	 * complexity: iterate over HASH_SIZE(h) and go through every node in list(k)
	 * O(h*k)
	 */
	double totWeight() const;

	/**
	 * copy constructor.
	 * complexity: iterate over HASH_SIZE(h) and go through every node in list(k)
	 * O(h*k);
	 */
	MyHashMap(const MyHashMap&);
private:
	MyHashMap& operator=(const MyHashMap&);
	// The lists of the hash table
	MyLinkedList _hashT[HASH_SIZE];
	unsigned int _size;
public:
	/**
	 * operator == check if current map has same weight like other map
	 * weight is measured with totWeight summing all data in all nodes.
	 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
	 * O(h1k1 +h2k2).
	 */
	bool operator== (const MyHashMap& other);

	/**
	 * operator > check if current map is bigger than other map
	 * weight is measured with totWeight summing all data in all nodes.
	 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
	 * O(h1k1 +h2k2).
	 */
	bool operator> (const MyHashMap& other);

	/**
	 * operator < check if current map is smaller than other map
	 * weight is measured with totWeight summing all data in all nodes.
	 * complexity: iterate on HASH_SIZE (h) and sum every node in list (k)
	 * O(h1k1 +h2k2).
	 */
	bool operator< (const MyHashMap& other);

	/**
	 * operator - return all the elements in a that are not intersect with.
	 * complexity: iterate once on all elements in a (m) and check if they intersect in relative
	 * lists in b (k): O(m*k);
	 */
	MyHashMap operator- (const MyHashMap& other);

	/**
	 * operator | is union on sets, a|b is all the elements in a and all the elements in b
	 * that are not in a, meaning an element in a will stay in a|b
	 * complexity: iterating once on all elements in a (m) and than  iterating on all elements in b(n)
	 * and checking relative list (k) meaning O(m+n*k).
	 */
	MyHashMap operator| (const MyHashMap& other);

	/**
	 * operation &- intersections. return all elements that are both in current and othe maps
	 * complexity: iterate on m lists, on each node we check isIntersect (k nodes in list) O(m*n*k)
	 */
	MyHashMap operator& (const MyHashMap& other);

	/**
	 * print the hashMap by rows
	 * complexity: m lists, n nodes in list O(m*n)
	 */
	void printMap() const;
};
#endif
