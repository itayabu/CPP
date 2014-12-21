/*
 * SparseMatrix.h
 *
 *  Created on: Aug 29, 2014
 *      Author: itayabu
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_

#include "MatrixInterface.h"
#include "Map.h"
/**
 * Sparse Matrix, implements the MatrixInterface for matrixes that hold mainly zeroes
 */
class SparseMatrix: public MatrixInterface
{

private:

	Map* _map;
	/**
	 * add arguments to the map
	 */
	void _addArgsFromArrayToMAp(double arr[]);

	/**
	 * helper function to printMatrix
	 */
	std::string _print(Pair a, double d);
public:

	/**
	 * implementation of iterator for sparse matrix
	 */
	class SparseIterator: public MatrixInterface::matrixIterator
	{

	private:
		Map* _iterMap;
		Map::iterator _selfIterator;

	public:
		/**
		 * build new iterator on a given map
		 */
		SparseIterator(Map* _iterMap);

		/**
		 * return the next element in map
		 */
		virtual std::pair<Pair, double> next();

		/**
		 * check if there is another element in map
		 */
		virtual bool hasNext();
	};

	/**
	 * multiply array with a selected row in matrix (dot product)
	 */
	double multRow(double arr[], int row);

	/**
	 * clone the matrix to a new matrix
	 */
	SparseMatrix* clone();

	/**
	 * return an iterator for the matrix
	 */
	matrixIterator* getIterator();

	/**
	 * constructor receiving an array of inputs and matrix sizes
	 */
	SparseMatrix(double arr[], unsigned int colSize, unsigned int rowSize);

	/**
	 * put the matrix into a string to be printed
	 */
	std::string printMatrix();

	/**
	 * default destructor
	 */
	virtual ~SparseMatrix();
};

#endif /* SPARSEMATRIX_H_ */
