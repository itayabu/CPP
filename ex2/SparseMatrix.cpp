/*
 * SparseMatrix.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: itayabu
 */

#include "SparseMatrix.h"
#include "Map.h"
#include <iostream>
#include<sstream>

/**
 * Sparse Matrix, implements the MatrixInterface for matrixes that hold mainly zeroes
 */
SparseMatrix::SparseMatrix(double arr[], unsigned int colSize, unsigned int rowSize)
{
	_map = new Map;
	_colSize = colSize;
	_rowSize = rowSize;
	_addArgsFromArrayToMAp(arr);
}

/**
 * add arguments to the map
 */
void SparseMatrix::_addArgsFromArrayToMAp(double arr[])
{
	int arrPlace = 0;
	for (unsigned int i = 0; i < _colSize; i++)
	{
		for (unsigned int j = 0; j < _rowSize; j++)
		{
			if (arr[arrPlace] > MY_EPSILON || arr[arrPlace] < -MY_EPSILON)
			{
				_map->insert(std::make_pair(std::make_pair(j, i), arr[arrPlace]));
			}
			arrPlace++;
		}
	}
}

/**
 * multiply array with a selected row in matrix (dot product)
 */
double SparseMatrix::multRow(double arr[], int row)
{
	SparseIterator iter = SparseIterator(&(*_map));
	double sum = 0;
	while (iter.hasNext())
	{
		std::pair<Pair, double> element = iter.next();

		if (element.first.first == (unsigned int) row)
		{
			sum += (element.second * arr[element.first.second]);
		}
	}
	return sum;
}

/**
 * return an iterator for the matrix
 */
SparseMatrix::matrixIterator* SparseMatrix::getIterator()
{
	return new SparseIterator(_map);
}

/**
 * put the matrix into a string to be printed
 */
std::string SparseMatrix::printMatrix()
{
	bool isEnd = false;
	std::string toReturn;
	SparseIterator iter = SparseIterator(_map);
	unsigned int col = 0, row = 0;
	Pair currentPair;
	// case matrix is empty
	if (!iter.hasNext())
	{
		return "0\n";
	}
	std::pair<Pair, double> element = iter.next();
	while (row < _rowSize)
	{
		currentPair = Pair(row, col);
		//case there are zeroes between iterations
		if (currentPair < element.first || isEnd)
		{
			toReturn += _print(currentPair, 0);
		}
		else
		{
			toReturn += _print(element.first, element.second);
			if (iter.hasNext())
			{
				element = iter.next();
			}
			else
			{
				isEnd = true;
			}
		}

		//update col and row
		if (col < _colSize - 1)
		{
			col++;
		}
		else
		{
			row++;
			col = 0;
		}
	}
	return toReturn;
}

/**
 * helper function to printMatrix
 */
std::string SparseMatrix::_print(Pair a, double d)
{
	std::stringstream str;
	if (a.second < _colSize - 1)
	{
		str << d << " , ";
	}
	else
	{
		str << d << "\n";
	}
	return str.str();
}

/**
 * clone the matrix to a new matrix
 */
SparseMatrix* SparseMatrix::clone()
{
	SparseIterator iter = SparseIterator(_map);
	unsigned int size = _colSize * _rowSize;
	double arr[size];
	for (unsigned int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
	std::pair<Pair, double> element;
	while (iter.hasNext())
	{
		element = iter.next();
		arr[element.first.first + element.first.second * _rowSize] = element.second;
	}
	return new SparseMatrix(arr, _colSize, _rowSize);
}

/**
 * build new iterator on a given map
 */
SparseMatrix::SparseIterator::SparseIterator(Map * iterMap)
{
	_iterMap = iterMap;
	_selfIterator = iterMap->begin();
}

/**
 * return the next element in map
 */
std::pair<Pair, double> SparseMatrix::SparseIterator::next()
{
	std::pair<Pair, double> temp = std::pair<Pair, double>((_selfIterator)->first,
			(_selfIterator)->second);
	_selfIterator++;
	return temp;
}

/**
 * check if there is another element in map
 */
bool SparseMatrix::SparseIterator::hasNext()
{
	return (!(_selfIterator == _iterMap->end()));
}

/**
 * default destructor
 */
SparseMatrix::~SparseMatrix()
{
	delete (_map);
}

