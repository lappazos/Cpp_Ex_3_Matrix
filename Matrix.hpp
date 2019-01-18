//
// Matrix.hpp

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#define TAB "\t"
#define DIM_MSG "There is no match between matrices dimensions"
#define OUT_OF_RANGE "Out Of Range"
#define ONE 1

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include "Complex.h"

/**
 * class of Dimension Exception
 */
class DimException : public std::exception
{
private:
    const char *_mError = DIM_MSG;

public:
    /**
     * override what
     * @return err msg
     */
    const char *what() const noexcept override
    {
        return _mError;
    }
};

/**
 * Generic Matrix class
 * @tparam T val type of Matrix elements
 */
template<class T>
class Matrix
{
public:
    /**
     * Default constructor
     * @throws std::bad_alloc
     */
    Matrix() : Matrix(ONE, ONE)
    {}

    /**
     * Constructor creates zero matrix
     * @param rows num of rows
     * @param cols num of cols
     * @throws std::bad_alloc
     */
    Matrix(unsigned int rows, unsigned int cols)
    {
        _r = rows;
        _c = cols;
        try
        {
            _matrix = std::vector<T>(_r * _c);
        }
        catch (std::bad_alloc &ba)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * Constructor initializing according to vec elements
     * @param rows num of rows
     * @param cols num of cols
     * @param cells val vector
     * @throws std::bad_alloc
     * @throws DimException
     */
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T> &cells)
    {
        _r = rows;
        _c = cols;
        if (cells.size() != rows * cols)
        {
            throw DimException();
        }
        try
        {
            _matrix = cells;
        }
        catch (std::bad_alloc &ba)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * copy Constructor
     * @param other mat to copy from
     * @throws std::bad_alloc
     */
    Matrix(const Matrix &other) = default;

    /**
     * destructor
     */
    ~Matrix() = default;

    /**
     * operator = overload
     * @throws std::bad_alloc
     */
    Matrix &operator=(const Matrix &other) = default;

    /**
     * operator + overload
     * @param other mat to add
     * @return new mat of sum
     * @throws DimException
     * @throws std::bad_alloc
     */
    Matrix operator+(const Matrix &other) const
    {
        if (_r != other._r or _c != other._c)
        {
            throw DimException();
        }
        auto ans = Matrix(*this);
        for (unsigned int i = 0; i < (_r * _c); i ++)
        {
            ans._matrix[i] = ans._matrix[i] + other._matrix[i];
        }
        return ans;
    }

    /**
     * operator - overload
     * @param other mat to deduct
     * @return new mat of result
     * @throws DimException
     * @throws std::bad_alloc
     */
    Matrix operator-(const Matrix &other) const
    {
        if (_r != other._r or _c != other._c)
        {
            throw DimException();
        }
        auto ans = Matrix(*this);
        for (unsigned int i = 0; i < (_r * _c); i ++)
        {
            ans._matrix[i] = ans._matrix[i] - other._matrix[i];
        }
        return ans;
    }

    /**
     * operator * overload
     * @param other mat to mult
     * @return new mat of mult
     * @throws DimException
     * @throws std::bad_alloc
     */
    Matrix operator*(const Matrix &other) const
    {
        if (_c != other._r)
        {
            throw DimException();
        }
        Matrix ans = Matrix(_r, other._c);
        for (unsigned int i = 0; i < _r; i ++)
        {
            for (unsigned int j = 0; j < other._c; j ++)
            {
                T temp = 0;
                for (unsigned int k = 0; k < _c; k ++)
                {
                    temp += (*this)(i, k) * other(k, j);
                }
                ans(i, j) = temp;
            }
        }
        return
                ans;
    }

    /**
     * operator == overload
     * @param other mat to compare
     * @return true if equal, false otherwise
     */
    bool operator==(const Matrix &other) const
    {
        return (_matrix == other._matrix and _r == other._r);
    }

    /**
     * operator != overload
     * @param other mat to compare
     * @return false if equal, true otherwise
     */
    bool operator!=(const Matrix &other) const
    {
        return ! (*this == other);
    }

    /**
     * create trans mat
     * @return trans mat
     * @throws DimException
     * @throws std::bad_alloc
     */
    Matrix trans() const
    {
        if (! isSquareMatrix())
        {
            throw DimException();
        }
        Matrix ans = Matrix(_c, _r);
        for (int i = 0; i < (_c * _r); i ++)
        {
            ans._matrix[i] = _matrix[(i / _c) + (i % _c) * _c];
        }
        return ans;
    }

    /**
     * check square mat
     * @return true if square, false otherwise
     */
    bool isSquareMatrix() const
    {
        return (_r == _c);
    }

    /**
     * operator << overload
     * @param os outstream
     * @param matrix mat to print
     * @return outstream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        for (int i = 0; i < matrix._r; i ++)
        {
            for (int j = 0; j < matrix._c; j ++)
            {
                os << matrix(i, j) << TAB;
            }
            os << std::endl;
        }
        return os;
    }

    /**
     * operator () overload
     * @param i row
     * @param j col
     * @return refrence to element in mat(i,j)
     * @throws std::out_of_range
     */
    T &operator()(unsigned int i, unsigned int j)
    {
        if ((0 <= i and i < _r) and (0 <= j and j < _c))
        {
            return _matrix[(i * _c) + j];
        }
        else
        {
            throw std::out_of_range(OUT_OF_RANGE);
        }
    }

    /**
     * operator () overload
     * @param i row
     * @param j col
     * @return element in mat(i,j)
     * @throws std::out_of_range
     */
    T operator()(unsigned int i, unsigned int j) const
    {
        if ((0 <= i and i < _r) and (0 <= j and j < _c))
        {
            return _matrix[(i * _c) + j];
        }
        else
        {
            throw std::out_of_range(OUT_OF_RANGE);
        }
    }

    /**
     * @return mat num of rows
     */
    unsigned int rows() const
    {
        return _r;
    }

    /**
     * @return mat num of cols
     */
    unsigned int cols() const
    {
        return _c;
    }

    typedef typename std::vector<T>::const_iterator const_iterator;

    /**
     * @return mat const end iterator
     */
    const_iterator end() const
    {
        return _matrix.end();
    }

    /**
     * @return mat const begin iterator
     */
    const_iterator begin() const
    {
        return _matrix.begin();
    }


private:
    std::vector<T> _matrix;
    unsigned int _r;
    unsigned int _c;
};

/**
 * specialized trans for Complex
 * @return trans mat
 * @throws DimException
 * @throws std::bad_alloc
 */
template<>
Matrix<Complex> Matrix<Complex>::trans() const
{
    if (! isSquareMatrix())
    {
        throw DimException();
    }
    Matrix ans = Matrix(_c, _r);
    for (unsigned int i = 0; i < (_c * _r); i ++)
    {
        ans._matrix[i] = _matrix[(i / _c) + (i % _c) * _c].conj();
    }
    return ans;
}

#endif //EX3_MATRIX_H
