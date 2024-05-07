#include "Matrices.h"
#include <cmath>

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        a.resize(_rows);

        for (int j = 0; j < _cols; ++j)
        {
            a[j].resize(_cols);
            for (int i = 0; i < _rows; ++i)
            {
                a[j][i] = 0;
            }
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b) //adding two matrices
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: rows and columns must be the same");
        }

        Matrix added(a.getRows(), a.getCols());

        for (int j = 0; j < a.getRows(); j++)
        {
            for (int i = 0; i < a.getCols(); i++)
            {
                added(j, i) = a(j, i) + b(j, i);
            }
        }
        return added;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) //multiplying 2 matrices
    {

        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: A's columns and B's rows must match");
        }

        Matrix mult(a.getRows(), b.getCols());

        for (int i = 0; i < b.getCols(); ++i)
        {
            for (int j = 0; j < a.getRows(); ++j)
            {
                double sum = 0;

                for (int k = 0; k < a.getCols(); ++k)
                {
                    sum += a(j, k) * b(k, i);
                }

                mult(j, i) = sum;
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
            for (int j = 0; j < a.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) < 0.001)
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

    ostream& operator<<(ostream& os, const Matrix& a) //output the matrix
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << a(i, j) << ' ';
            }
            os << '\n';
        }

        return os;
    } 

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; ++j)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}