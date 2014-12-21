/*
 * MapInterfce.h
 *
 *  Created on: Aug 29, 2014
 *      Author: itayabu
 */

#ifndef MAPINTERFCE_H_
#define MAPINTERFCE_H_
#include "Map.h"
#include <iostream>
#define MY_EPSILON 0.00001



/**
 * interface for the matrix classes.
 */
class MatrixInterface
{
protected:
	unsigned int _colSize, _rowSize;

public:
	/**
	 * iterator for the matrix
	 */
	class matrixIterator
	{
	public:

		/**
		 * basic constructor
		 */
		matrixIterator(){};

		/**
		 * return the next element of matrix
		 */
		virtual std::pair<Pair, double>  next() = 0;

		/**
		 * return true iff there exist another element in matrix
		 */
		virtual bool hasNext() = 0;

		/**
		 * basic destructor
		 */
		virtual ~matrixIterator(){};
	};

	/**
	 * return matrix'es col size
	 */
	inline unsigned int getCols()
	{
		return _colSize;
	}

	/**
	 * return the matrix'es row size
	 */
	inline unsigned int getRows()
	{
		return _rowSize;
	}

	/**
	 * clone the matrix to a new matrix
	 */
	virtual MatrixInterface* clone() = 0;

	/**
	 * return an iterator for the matrix
	 */
	virtual matrixIterator* getIterator() = 0;

	/**
	 * multiply array with a selected row in matrix (dot product)
	 */
	virtual double multRow(double arr[], int row) = 0;

	/**
	 * default destructor
	 */
	virtual ~MatrixInterface(){}

	/**
	 * put the matrix into a string to be printed
	 */
	virtual std::string printMatrix() = 0;
};

#endif /* MAPINTERFCE_H_ */
