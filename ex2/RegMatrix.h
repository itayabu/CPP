/*
 * RegMatrix.h
 *
 *  Created on: Aug 31, 2014
 *      Author: itayabu
 */

#ifndef REGMATRIX_H_
#define REGMATRIX_H_
#include "Vector.h"
#include "MatrixInterface.h"
#include<sstream>

/**
 * regular Matrix, implements the MatrixInterface for normal matrixes
 */
class RegMatrix: public MatrixInterface
{
private:
	Vector2D *_vector;


public:

	/**
	 * implementation of iterator for sparse matrix
	 */
	class Vector2DIterator: public MatrixInterface::matrixIterator
	{
	private:

		/**
		 * advaces row\col to the next element
		 */
		void _goNext();
	public:
		Vector2D * _vectorToIter;
		unsigned int _colPlace, _rowPlace;

		/**
		 * basic constructor, receive a vector to iterate upon.
		 */
		Vector2DIterator(Vector2D * vec);

		/**
		 * return true iff current matrix did not end
		 */
		bool hasNext();

		/**
		 * return an element and advances the iterator
		 */
		std::pair<Pair, double> next();

	};
	/**
	 * multiply array with a selected row in matrix (dot product)
	 */
	virtual double multRow(double arr[], int row);

	/**
	 * put the matrix into a string to be printed
	 */
	std::string printMatrix();

	/**
	 * clone the matrix to a new matrix
	 */
	RegMatrix* clone();

	/**
	 * return an iterator for the matrix
	 */
	matrixIterator * getIterator();

	/**
	 * constructor receiving an array of inputs and matrix sizes
	 */
	RegMatrix(double arr[], unsigned int colSize, unsigned int rowSize);

	/**
	 * default destructor
	 */
	virtual ~RegMatrix();

};

#endif /* REGMATRIX_H_ */
