#include <iostream>
#include "matrix.h"

Matrix::Matrix():
rows {1},
columns {1},
numElements {rows * columns},
M {new int[numElements]}
{}

Matrix::Matrix(int n):
rows {n},
columns {n},
numElements {n * n},
M {new int[numElements]}
{}

Matrix::Matrix(int n, int m):
rows {n},
columns {m},
numElements {rows * columns},
M {new int[numElements]}
{}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> l):
rows {l.size()},
columns {l.begin()->size()},
numElements {rows * columns},
M {new int[numElements]}
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
    if (B.numElements == 1)
    {
        return B(0,0);
    }

    int total = 0;
    for (int i = 0; i < B.columns; ++i)
    {
        Matrix minor(B.rows - 1);
        int cofactor = i % 2 == 0 ? 1 : -1;
        int tracker = i + B.columns;
        int minor_position = 0;
        for (int j = B.columns; j < B.numElements; ++j)
        {
            if (tracker == j)
            {
                tracker += B.columns;
                continue;
            }
            minor.M[minor_position] = B.M[j];
            minor_position++;
        }
        total += cofactor * B(0,i) * laplace_expansion(minor);
    }
    return total;
}

int Matrix::get_determinant()
{
    return laplace_expansion(*this);
}