#include "Matrix.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
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
        int rows = a.getRows();
        int cols = a.getCols();

        Matrix added(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                added(i, j) = a(i, j) + b(i, j);
            }
        }

        return added;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) //multiplying 2 matrices
    {
        int rowsA = a.getRows();
        int colsA = a.getCols();
        int colsB = b.getCols();

        Matrix mult(rowsA, colsB);

        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsB; ++j)
            {
                double sum = 0.0;

                for (int k = 0; k < colsA; ++k)
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
        } //see if number of row and cols are the same

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (a(i, j) != b(i, j))
                {
                    return false;
                }
            }
        } //see if each element is same

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
        a[0][1] = 0.0;
        a[1][0] = 0.0;
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