#include "matrix.h"
#include <iostream>

Matrix::Matrix():
rows {2},
columns {2},
dimension {rows * columns},
M {new int[dimension]}
{
    for (int i = 0; i < dimension; ++i)
    {
        M[i] = i + 1;
    }
}

Matrix::Matrix(int n):
rows {n},
columns {n},
dimension {n * n},
M {new int[dimension]}
{
    for (int i = 0; i < dimension; ++i)
    {
        M[i] = i + 1;
    }
}

Matrix::Matrix(int n, int m):
rows {n},
columns {m},
dimension {rows * columns},
M {new int[dimension]}
{
    for (int i = 0; i < dimension; ++i)
    {
        M[i] = i + 1;
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> l):
rows {l.size()},
columns {l.begin()->size()},
dimension {rows * columns},
M {new int[dimension]}
{
    int n = 0;
    int m = 0;
    for (const auto& i : l)
    {
        for (const auto& j : i)
        {
            M[(n * columns) + m] = j;
            ++m;
        }
        m = 0;
        ++n;
    }
}

Matrix::~Matrix()
{
    delete[] M;
}

int Matrix::operator()(int n, int m)
{
    return M[(n * columns) + m];
}

int Matrix::laplace_expansion(Matrix& B)
{
    if (B.dimension == 1)
    {
        return B(0,0);
    }

    int total = 0;
    for (int i = 0; i < B.rows; ++i)
    {
        Matrix minor {B.rows - 1};
        int cofactor = i % 2 == 0 ? 1 : -1;
        for (int j = 0; j < minor.rows; ++j)
        {
            for (int k = 0; k < minor.columns; ++k)
            {
                if (cofactor > 0)
                {
                    minor.M[(j * minor.columns) + k] = B(j+1,k+1);
                }
                else
                {
                    int col = k % 2 == 0 ? k : k + 1;
                    minor.M[(j * minor.columns) + k] = B(j+1, col);
                }
            }
        }
        total += cofactor * B(0,i) * laplace_expansion(minor);
    }
    return total;
}

const int Matrix::get_determinant()
{
    return laplace_expansion(*this);
}