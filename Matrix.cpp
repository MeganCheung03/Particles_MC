#include "Matrices.h"
#include <cmath>

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        a.resize(_rows);
        for (int i = 0; i < _rows; i++)
        {
            a[i].resize(_cols);
            for (int j = 0; j < _cols; j++)
            {
                a[i][j] = 0;
            }
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: A and B's rows must match, same with the columns");
        }

        Matrix added(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                added(i, j) = a(i, j) + b(i, j);
            }
        }
        return added;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: A's rows must equal B's rows");
        }

        Matrix mult(a.getRows(), b.getCols());

        for (int j = 0; j < b.getCols(); j++)         
        {
            for (int i = 0; i < a.getRows(); i++)     
            {
                double sum = 0;
                for (int k = 0; k < a.getCols(); k++)   
                {
                    sum += a(i, k) * b(k, j);
                }
                mult(i, j) = sum;
            }
        }
        return mult;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int k = 0; k < a.getCols(); k++)
            {
                if (abs(a(i, k) - b(i, k)) < 0.001)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Matrix& a) 
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int k = 0; k < a.getCols(); k++)
            {
                os << a(i, k) << " ";
            }
            os << '\n';
        }
        return os;
    } 

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);

        (*this)(0, 0) = cosTheta; 
        (*this)(0, 1) = -sinTheta; 
        (*this)(1, 0) = sinTheta; 
        (*this)(1, 1) = cosTheta;
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; j++)
        {
            (*this)(0, j) = xShift;
            (*this)(1, j) = yShift;
        }
    }
}