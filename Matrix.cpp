#include "Matrices.h"
#include <cmath>

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        a.resize(_rows);

        for (int j = 0; j < _cols; ++j)
        {
            for (int i = 1; i < _rows; ++i)
            {
                a[j][i] = 0;
            }
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b) //adding two matrices
    {
        int rowsA = a.getRows();
        int rowsB = b.getRows();
        int colsA = a.getCols();
        int colsB = b.getCols();

        Matrix added(rowsA, colsA);

        if (rowsA != rowsB || colsA != colsB)
        {
            throw runtime_error("Error: rows and columns must be the same number");
        }

        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsA; ++j)
            {
                added(i, j) = a(i, j) + b(i, j);
            }
        }

        return added;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) //multiplying 2 matrices
    {
        int rowsA = a.getRows();
        int rowsB = b.getRows();
        int colsA = a.getCols();
        int colsB = b.getCols();

        Matrix mult(rowsA, colsB);

        if (colsA != rowsB)
        {
            throw runtime_error("Error: A's columns and B's rows must match");
        }

        for (int i = 0; i < colsB; ++i)
        {
            for (int j = 0; j < rowsA; ++j)
            {
                double sum = 0.0;

                for (int k = 0; k < colsA; ++k)
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

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (a(i, j) != b(i, j))
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
        int rows = a.getRows();
        int cols = a.getCols();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
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