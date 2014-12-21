/*
 * Matrix.hpp
 *
 *  Created on: Sep 7, 2014
 *      Author: itayabu
 */
#include <vector>
#include "Rational.h"
#include <iterator>
#include <list>

/**
 * exception master class for exception in matrixes.
 */
class MatrixException:std::exception
{
	std::string what()
	{
		return "general problem in matrix";
	}
};

/**
 * matrix exception for plus operation, thrown when cols or rows dont match.
 */
class MatPlusException:MatrixException
{
	std::string what()
	{
		return "not matching sizes of matrixes for operation +";
	}
};

/**
 * matrix null exception, thrown when bad inputs are given to matrix
 */
class MatNULLException:MatrixException
{
	std::string what()
	{
		return "cannot have matrix with zero rows or zero cols";
	}
};

/**
 * matrix exception for multiplying. thrown when bad match for cols and rows arize.
 */
class MatMultException:MatrixException
{
	std::string what()
	{
		return "bad sizes for matrixes for operation *";
	}
};



/**
 * Generic Matrix class.
 *
 */
template <class T> class Matrix
{
private:
	unsigned int _rows;
	unsigned int _cols;
	std::vector<std::vector<T>> _vec;

	/**
	 * set arguments from constructors to class members.
	 */
	void _setMatrix(const unsigned int rows, const unsigned int cols)
	{
		if (rows == 0 || cols == 0)
		{
			throw MatNULLException();
		}
		_rows = rows;
		_cols = cols;
		_vec.resize(rows);
		for (unsigned int i = 0; i < rows; i++)
		{
			_vec.at(i).resize(cols);
		}
	}

public:
	/**
	 * operator<< for stream insertion
	 * */
	template <typename Y> friend std::ostream& operator<< (std::ostream &os, const Matrix<Y>& mat);

	template <typename Y> friend void std::swap(Matrix<Y>& first, Matrix<Y>& second);

	/**
	 * binary multiply for scalar on matrix.
	 */
	template <typename Y>friend Matrix<Y> operator* (Y& scalar, Matrix<Y>& mat);


	/**
	 * basic constructor.
	 * constructor build a 1X1 matrix and put default argument in matrix's entrance.
	 */
	Matrix<T>()
	{
		_setMatrix(1, 1);
		_vec.at(0).at(0) = T();
	}

	/**
	 * vector constructor.
	 * constructor receive number of row, cols and a vector with matrix'es values.
	 */
	Matrix<T>(const unsigned int rows, const unsigned int cols, std::vector<T> copyVec)
	{
		_setMatrix(rows, cols);
		typename std::vector<T>::iterator iter = copyVec.begin();
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				_vec.at(i).at(j) = *(iter.operator ->());
				iter++;
			}
		}
	}

	/**
	 * copy constructor
	 */
	Matrix<T> (const Matrix<T>& other)
	{
		_setMatrix(other._rows, other._cols);
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				_vec.at(i).at(j) = other._vec.at(i).at(j);
			}
		}
	}

	/**
	 *  move constructor
	 */
	Matrix<T> (Matrix<T> && other)
	{
		std::swap( *this, other);
	}

	/**
	 *  assignment operator
	 */
	Matrix<T>& operator=(Matrix<T> other)
	{
		swap ( *this, other);
		return *this;
	}

	/**
	 * plus operator
	 */
	Matrix<T> operator+ (const Matrix<T>& other)
	{
		if (_cols != other._cols || _rows != other._rows)
		{
			throw MatPlusException();
		}
		Matrix<T> temp = Matrix<T>( *this);
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				temp._vec.at(i).at(j) = other._vec.at(i).at(j) + _vec.at(i).at(j);
			}
		}
		return temp;
	}

	/**
	 * multiply operator matrix on matrix
	 */
	Matrix<T> operator* (const Matrix<T>& other)
	{
		if (_cols != other._rows)
		{
			throw MatMultException();
		}
		std::vector<T> tempVec;
		tempVec.resize(_rows * other._cols);
		unsigned int vecPlace = 0;
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int l = 0; l < other._cols; l++)
			{
				T t = T();
				for (unsigned int j = 0; j < _cols; j++)
				{
					t = t + (_vec.at(i).at(j)) * (other._vec.at(j).at(l));
				}
				tempVec.at(vecPlace) = t;
				vecPlace++;
			}
		}
		return Matrix<T>(_rows, other._cols, tempVec);
	}

	/**
	 * multiply operator matrix on scalar
	 */
	Matrix<T> operator* (const T& scalar)
	{
		std::vector<T> tempVec;
		tempVec.resize(_rows * _cols);
		unsigned int vecPlace = 0;
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j <_cols; j++)
			{
				tempVec.at(vecPlace ++) = _vec.at(i).at(j) * scalar;
			}
		}
		return Matrix<T>(_rows, _cols, tempVec);
	}

	/**
	 * traspose the matrix, every element's cols and rows switch
	 */
	Matrix<T> transpose()
	{
		std::vector<T> tempVec;
		tempVec.resize(_cols * _rows);
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				tempVec.at(j * _rows + i) = _vec.at(i).at(j);
			}
		}
		return Matrix<T>(_cols, _rows, tempVec);
	}

	/**
	 * generic hasTrace function.
	 * if matrix is sqare, return true and put trace value in the given input.
	 * if matrix is not sqare return false.
	 */
	template <typename Y> bool hasTrace (Y& y)
	{
		y = T();
		if (_rows != _cols)
		{
			return false;
		}
		for (unsigned int i = 0; i < _rows; i++)
		{
			y += _vec.at(i).at(i);
		}
		return true;
	}

	/**
	 * special hasTrace for Rational numbers.
	 * if matrix is sqare, return true and put trace value in the given input.
	 * if matrix is not sqare return false.
	 */
	bool hasTrace (Rational & rat)
	{
		std::cout << "Performing specialized function of trace for Rational values" << std::endl;
		if (_rows != _cols)
		{
			rat = Rational();
			return false;
		}
		long int denominator = 1;
		for (unsigned int i = 0; i < _rows; i++)
		{

			denominator *=  (_vec.at(i).at(i).getDenominator());
		}
		long int numerator = 0;

		for (unsigned int i = 0; i < _rows; i++)
		{
			numerator = numerator + (_vec.at(i).at(i)).getNumerator() *
					(denominator / (_vec.at(i).at(i).getDenominator()));
		}
		rat = Rational (numerator, denominator);
		return true;
	}

	/**
	 * swap function for Matrixes, using std::swap function
	 */
	template <typename Y> void swap(Matrix<Y>& first, Matrix<Y>& second)
	{
		std::swap (first._vec, second._vec);
		std::swap (first._rows, second._rows);
		std::swap (first._cols, second._cols);
	}
};

/**
 * binary multiply for scalar on matrix.
 */
template <typename Y> Matrix<Y> operator* (Y& scalar, Matrix<Y>& mat)
{
	return mat.operator* (scalar);
}

/**
 * operator<< for stream insertion.
 */
template <class T> std::ostream& operator<<(std::ostream &os, const Matrix<T> & mat)
{
	for (unsigned int i = 0; i < mat._rows-1; i++)
	{
		for (unsigned int j = 0; j < mat._cols; j++)
		{
			os << mat._vec.at(i).at(j) << " ";
		}
		os << "\n";
	}
	for (unsigned int j = 0; j < mat._cols - 1; j++)
	{
		os << mat._vec.at(mat._rows - 1).at(j) << " ";
	}
	os << mat._vec.at(mat._rows - 1).at(mat._cols - 1) << "\n";
	return os;
}

