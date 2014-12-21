/*
 * MyMatrix.h
 *
 *  Created on: Sep 1, 2014
 *      Author: itayabu
 */

#ifndef MYMATRIX_H_
#define MYMATRIX_H_

#include "MatrixInterface.h"
#include "SparseMatrix.h"
#include "RegMatrix.h"
#include <iostream>

/**
 * MyMatrix class.
 * implements operations on matrixes.
 * when to change matrix implement: as I saw it, every add could change the matrix,
 * (reg a+(-a), sparse a+a ect...) so I put the decision to be made every time I build a new
 * matrix.
 */
class MyMatrix
{
private:
	MatrixInterface * matPointer;
public:


	/**
	 * constructor from array. receive an array of numbers and sizes of the matrix
	 */
	MyMatrix(double arr[], unsigned int colSize, unsigned int rowSize);

	/**
	 * copy costructor
	 */
	MyMatrix(const MyMatrix& other);

	/**
	 * constructor from string.
	 */
	MyMatrix(std::string matString);

	/**
	 * plus operator for matrixes.
	 */
	MyMatrix operator+(const MyMatrix& other)const;

	/**
	 * NEG operation on a matrix, make every element its own negative
	 */
	MyMatrix operator-() const;

	/**
	 * adding the other matrix to current one
	 */
	MyMatrix& operator+=(const MyMatrix& other);

	/**
	 * reducing the other matrix from current one.
	 */
	MyMatrix& operator-=(const MyMatrix& other);

	/**
	 * isEqual operator on matrixes
	 */
	virtual bool operator==(const MyMatrix& other);

	/**
	 * transpose the matrix, cols to rows and rows to cols
	 */
	MyMatrix transpose() const;

	/**
	 * minus operation for matrixes.
	 */
	MyMatrix operator-(const MyMatrix& other) const;

	/**
	 * assignment operator
	 */
	MyMatrix& operator=(const MyMatrix& other);

	/**
	 * mult operation on matrixes.
	 */
	MyMatrix operator*(const MyMatrix& other);

	/**
	 * Multiplying matrix by other one.
	 */
	MyMatrix& operator*=(const MyMatrix& other);

	/**
	 * calculating all the elements on main diagonal
	 */
	virtual double trace();

	/**
	 * calculate the frobenious norm of the matrix
	 */
	double frobeniusNorm();

	/**
	 * out stream operation for matrixes, used to draw the matrix out
	 */
	friend std::ostream& operator<<(std::ostream&, const MyMatrix&);

	/**
	 * default destructor
	 */
	virtual ~MyMatrix();

};

/**
 * out stream operation for matrixes, used to draw the matrix out
 */
std::ostream& operator<<(std::ostream& os, const MyMatrix & mat);


#endif /* MYMATRIX_H_ */
