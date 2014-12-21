/*
 * RegMatrix.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: itayabu
 */

#include "RegMatrix.h"
#include <iostream>

/**
 * constructor receiving an array of inputs and matrix sizes
 */
RegMatrix::RegMatrix(double arr[], unsigned int colSize, unsigned int rowSize)
//_colSize(colSize) , _rowSize(rowSize)
{
	_vector = new Vector2D;
	_colSize = colSize;
	_rowSize = rowSize;
	// initializng the 2Dvector
	_vector->resize(_rowSize);
	for (unsigned int i = 0; i < _rowSize; i++)
	{
		_vector->at(i).resize(_colSize);
	}
	int arrPlace = 0;
	for (unsigned int i = 0; i < _colSize; i++)
	{
		for (unsigned int j = 0; j < _rowSize; j++)
		{
			(*_vector)[j][i] = arr[arrPlace];
			arrPlace++;
		}
	}
}

/**
 * return an iterator for the matrix
 */
RegMatrix::matrixIterator * RegMatrix::getIterator()
{
	return new Vector2DIterator(&(*_vector));
}

/**
 * clone the matrix to a new matrix
 */
RegMatrix* RegMatrix::clone()
{
	Vector2DIterator iter = Vector2DIterator(_vector);
	double arr[_colSize * _rowSize];
	for (unsigned int i = 0; i < _colSize * _rowSize; i++)
	{
		arr[i] = 0;
	}
	std::pair<Pair, double> element;
	while (iter.hasNext())
	{
		element = iter.next();
		arr[element.first.first + element.first.second * _rowSize] = element.second;
	}
	return new RegMatrix(arr, _colSize, _rowSize);
}

/**
 * default destructor
 */
RegMatrix::~RegMatrix()
{
	delete (_vector);
}

/**
 * multiply array with a selected row in matrix (dot product)
 */
double RegMatrix::multRow(double arr[], int row)
{
	double sum = 0;
	for (unsigned int i = 0; i < _colSize; i++)
	{
		sum += (arr[i] * (*_vector)[row][i]);
	}
	return sum;
}

/**
 * basic constructor, receive a vector to iterate upon.
 */
RegMatrix::Vector2DIterator::Vector2DIterator(Vector2D* vec)
{
	_vectorToIter = vec;
	_rowPlace = _colPlace = 0;
}

/**
 * return true iff current matrix did not end
 */
bool RegMatrix::Vector2DIterator::hasNext()
{
	return (_rowPlace < _vectorToIter->size());
}

/**
 * return an element and advances the iterator
 */
std::pair<Pair, double> RegMatrix::Vector2DIterator::next()
{
	//	std::vector <double> a = _vectorToIter->at(0)
	double aa = (*_vectorToIter)[_rowPlace][_colPlace];
	std::pair<Pair, double> zz = std::pair<Pair, double>(Pair(_rowPlace, _colPlace), aa);
	_goNext();
	return zz;
}

/**
 * advaces row\col to the next element
 */
void RegMatrix::Vector2DIterator::_goNext()
{
	if (_colPlace < (_vectorToIter->at(0).capacity() - 1))
	{
		_colPlace++;
	}
	else
	{
		_colPlace = 0;
		_rowPlace++;
	}

}

/**
 * put the matrix into a string to be printed
 */
std::string RegMatrix::printMatrix()
{
	std::stringstream str;
	Vector2DIterator * iter = (Vector2DIterator*) getIterator();

	while (iter->hasNext())
	{
		if (iter->_colPlace == _colSize - 1)
		{
			str << iter->next().second << "\n";
		}
		else
		{
			str << iter->next().second;
			str << " , ";

		}
	}
	delete (iter);
	return str.str();
}

