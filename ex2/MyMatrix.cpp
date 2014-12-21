/*
 * MyMatrix.cpp
 *
 *  Created on: Sep 1, 2014
 *      Author: itayabu
 */

#include "MyMatrix.h"
#include <iostream>
#include <stdlib.h>

/**
 * constructor from array. receive an array of numbers and sizes of the matrix
 */

MyMatrix::MyMatrix(double arr[], unsigned int colSize, unsigned int rowSize)
{
	int zeroes = 0;
	int arrSize = colSize * rowSize;
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] < MY_EPSILON && arr[i] > -MY_EPSILON)
		{
			zeroes++;
		}
	}
	if (zeroes > (arrSize / 2))
	{
		matPointer = new SparseMatrix(arr, colSize, rowSize);
	}
	else
	{
		matPointer = new RegMatrix(arr, colSize, rowSize);
	}
}

/**
 * copy constructor
 */
MyMatrix::MyMatrix(const MyMatrix& other)
{
	matPointer = other.matPointer->clone();
}

/**
 * constructor from string.
 */
MyMatrix::MyMatrix(std::string matString)
{
	std::istringstream stream(matString);
	Vector vec;
	unsigned int cols, rows, i;
	unsigned int zeroes = 0;
	std::string line, curr;

	//parse string to a vector
	for (rows = 0; std::getline(stream, line); rows++)
	{
		cols = 0;
		std::stringstream streamLine(line);
		while (streamLine >> curr)
		{
			if (curr == ",")
			{
				continue;
			}
			i++;
			std::stringstream stringToDouble;
			double num = 0;
			stringToDouble << curr;
			stringToDouble >> num;
			if (num - 0 < MY_EPSILON && num > -MY_EPSILON)
			{
				zeroes++;
			}
			vec.push_back(num);
			cols++;
		}
	}

	//put vector in array of correct places
	unsigned int arrSize = rows * cols;
	double arr[arrSize];
	for (i = 0; i < arrSize; i++)
	{
		arr[i] = vec[(i * cols) % (arrSize - 1)];
	}
	arr[arrSize - 1] = vec[arrSize - 1];

	//choose matrix representation
	if (zeroes > (rows * cols / 2))
	{
		matPointer = new SparseMatrix(arr, cols, rows);
	}
	else
	{
		matPointer = new RegMatrix(arr, cols, rows);
	}
}

/**
 * assignment operator
 */
MyMatrix& MyMatrix::operator=(const MyMatrix& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete (matPointer);
	matPointer = other.matPointer->clone();

	return *this;
}

/**
 * isEqual operator on matrixes
 */
bool MyMatrix::operator==(const MyMatrix& other)
{
	//check sizes
	if (matPointer->getCols() != other.matPointer->getCols() ||
		matPointer->getRows() != other.matPointer->getRows())
	{
		return false;
	}
	//build a new matrix with minus operation, if matrixes are equal, new matrix will be empty
	MyMatrix check = *this - other;
	MatrixInterface::matrixIterator* iterate = check.matPointer->getIterator();
	std::pair<Pair, double> element;
	while (iterate->hasNext())
	{
		element = iterate->next();
		if (element.second > MY_EPSILON || element.second < -MY_EPSILON)
		{
			delete (iterate);
			return false;
		}
	}
	delete (iterate);
	return true;
}

/**
 * plus operator for matrixes.
 */
MyMatrix MyMatrix::operator+(const MyMatrix& other) const
{
	int matSize = (matPointer->getCols() * matPointer->getRows());
	double arr[matSize];
	for (int i = 0; i < matSize; i++)
	{
		arr[i] = 0;
	}

	//adding first matrix to array
	std::pair<Pair, double> element;
	MatrixInterface::matrixIterator* iterate = matPointer->getIterator();
	while (iterate->hasNext())
	{
		element = iterate->next();
		arr[element.first.first + element.first.second * matPointer->getRows()] =
				element.second;
	}
	delete (iterate);

	//adding second matrix to array
	iterate = other.matPointer->getIterator();
	while (iterate->hasNext())
	{
		element = iterate->next();
		arr[element.first.first + element.first.second * matPointer->getRows()] +=
				element.second;
	}
	delete (iterate);
	return MyMatrix(arr, matPointer->getCols(), matPointer->getRows());
}

/**
 * minus operation for matrixes.
 */
MyMatrix MyMatrix::operator-() const
{
	int matSize = (matPointer->getCols() * matPointer->getRows());
	double arr[matSize];
	MatrixInterface::matrixIterator* iterate = matPointer->getIterator();
	std::pair<Pair, double> element;
	for (int i = 0; i < matSize; i++)
	{
		arr[i] = 0;
	}
	while (iterate->hasNext())
	{
		element = iterate->next();
		arr[element.first.first + element.first.second * matPointer->getRows()] = - element.second;
	}
	delete (iterate);
	return MyMatrix(arr, matPointer->getCols(), matPointer->getRows());
}

/**
 * minus operation for matrixes.
 */
MyMatrix MyMatrix::operator-(const MyMatrix& other) const
{
	MyMatrix a = other.operator -();
	return (*this + a);
}

/**
 * adding the other matrix to current one
 */
MyMatrix& MyMatrix::operator+=(const MyMatrix& other)
{
	*this = (*this + other);
	return *this;
}

/**
 * reducing the other matrix from current one.
 */
MyMatrix& MyMatrix::operator-=(const MyMatrix& other)
{
	*this = (*this - other);
	return *this;
}

/**
 * calculating all the elements on main diagonal
 */
double MyMatrix::trace()
{
	if (matPointer->getCols() != matPointer->getRows())
	{
		return 0;
	}
	double sum = 0;
	std::pair<Pair, double> element;
	MatrixInterface::matrixIterator* iterate = matPointer->getIterator();
	while (iterate->hasNext())
	{
		//adding only elements on diagonal
		element = iterate->next();
		if (element.first.first == element.first.second)
		{
			sum += element.second;
		}
	}
	delete (iterate);
	return sum;
}

/**
 * mult operation on matrixes.
 */
MyMatrix MyMatrix::operator*(const MyMatrix& other)
{
	bool hasChanged = false;
	//by trasposing, we can multiply row to row
	MyMatrix transposed = other.transpose();
	double rowArr[matPointer->getCols()];
	unsigned int size = (matPointer->getRows() * transposed.matPointer->getRows());
	double arr[size];
	for (unsigned int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
	std::pair<Pair, double> element;
	int rowToMult = -1;

	MatrixInterface::matrixIterator* iterate = matPointer->getIterator();
	if (!iterate->hasNext())
	{
		delete (iterate);
		return MyMatrix(arr, transposed.matPointer->getRows(),
				matPointer->getRows());
	}
	element = iterate->next();
	while (iterate->hasNext() || rowToMult < (int) transposed.matPointer->getRows())
	{
		hasChanged = false;

		//case iterator didnt advance in this round, the rest of matrix is zeroes.
		if ((int) element.first.first == rowToMult)
		{
			delete (iterate);
			return MyMatrix(arr, transposed.matPointer->getRows(),
					matPointer->getRows());
		}

		//else, build array for a row to mult by the other matrix
		for (unsigned int i = 0; i < matPointer->getCols(); i++)
		{
			rowArr[i] = 0;
		}

		rowToMult = element.first.first;

		//put values in the array as long as they are from the same row in the matrix
		while ((int) element.first.first == rowToMult)
		{
			rowArr[element.first.second] = element.second;
			hasChanged = true;
			if (!iterate->hasNext())
			{
				break;
			}
			if (iterate->hasNext())
			{
				element = iterate->next();
			}
		}

		//if there are values in the array, multiply this row wit every row in transposed matrix.
		if (hasChanged)
		{
			for (unsigned int i = 0; i < transposed.matPointer->getRows(); i++)
			{
				arr[rowToMult + matPointer->getRows() * i] =
						transposed.matPointer->multRow(rowArr, i);
			}
		}
	}
	delete (iterate);
	return MyMatrix(arr, transposed.matPointer->getRows(), matPointer->getRows());
}

/**
 * Multiplying matrix by other one.
 */
MyMatrix& MyMatrix::operator*=(const MyMatrix& other)
{
	*this = (*this * other);
	return *this;
}

/**
 * transpose the matrix, cols to rows and rows to cols
 */
MyMatrix MyMatrix::transpose() const
{
	double arr[matPointer->getCols() * matPointer->getRows()];
	for (unsigned int i = 0; i < matPointer->getCols() * matPointer->getRows(); i++)
	{
		arr[i] = 0;
	}
	MatrixInterface::matrixIterator* iterate = matPointer->getIterator();
	std::pair<Pair, double> element;
	while (iterate->hasNext())
	{
		element = iterate->next();

		//switch rows and cols to the new array
		arr[(element.first.first * matPointer->getCols()) + element.first.second] =
				element.second;
	}
	delete (iterate);
	return MyMatrix(arr, matPointer->getRows(), matPointer->getCols());
}

/**
 * default destructor
 */
MyMatrix::~MyMatrix()
{
	delete (matPointer);
}

/**
 * calculate the frobenious norm of the matrix
 */
double MyMatrix::frobeniusNorm()
{
	return (*this * this->transpose()).trace();
}

/**
 * out stream operation for matrixes, used to draw the matrix out
 */
std::ostream& operator<<(std::ostream& os, const MyMatrix & mat)
{
	os << mat.matPointer->printMatrix();
	return os;
}
