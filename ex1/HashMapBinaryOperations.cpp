/*
 * HashMapBinaryOperations.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: rosenavi
 */
#include <iostream>
#include <string>
#include "MyHashMap.h"

#define NUM_ARRAYS 2
#define FIRST_MAP 0
#define SECOND_MAP 1


/**
 * demonstrate overloading operations usage.
 */
int main()
{
	//initialize:
	std::cout << "we will build a few maps to demostrate upon." << std::endl;
	MyHashMap setsArr[NUM_ARRAYS];
	setsArr[FIRST_MAP].add("half", 0.5);
	setsArr[FIRST_MAP].add("pai", 3.174);
	setsArr[FIRST_MAP].add("theAnswer", 42);
	setsArr[SECOND_MAP].add("goldenLine", 1.67);
	setsArr[SECOND_MAP].add("mayTheForce", 5.4);
	setsArr[SECOND_MAP].add("theAnswer", 24);
	std::cout << "for start, lets have two maps:" << std::endl;
	std::cout << "First map:" << std::endl;
	setsArr[FIRST_MAP].printMap();
	std::cout << "second map:" << std::endl;
	setsArr[SECOND_MAP].printMap();

	//equasion operations:

	std::cout << "we will see that first map's weight is " << setsArr[FIRST_MAP].totWeight()
					<< std::endl;
	std::cout << "and second's map's weight is " << setsArr[SECOND_MAP].totWeight()
						<< std::endl;
	std::cout << "therefore, first map is bigger, and indeed first map == second map is " <<
			(setsArr[0] == setsArr[1]) << ", means false." << std::endl;
	std::cout << "also first map < second map is " <<
			(setsArr[0] < setsArr[1]) << ", means false." << std::endl;
	std::cout << "but first map > second map is " <<
			(setsArr[0] > setsArr[1]) << ", means true." << std::endl;

	// minus operation
	std::cout << "we saw that theAnswer is both in map one and in map two,/n minus operation on sets"
			" (first map- second map) will give us first map without theAnswer" << std::endl;
	//MyHashMap:: MyHashMap map = (setsArr[0] - setsArr[1]);
	(setsArr[0] - setsArr[1]).printMap();

	std::cout << "intersect operation on two maps will bring only 'theAnswer'" << std::endl;
	(setsArr[0] & setsArr[1]).printMap();

	//union operation
	std::cout << "we will see that union operation (first map | second map) keep first map's "
			"'theAnswer' value of 42:" << std::endl;
	//setsArr[2]= setsArr[0]|setsArr[1];
	(setsArr[0] | setsArr[1]).printMap();
}
