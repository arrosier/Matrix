#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

class Matrix
{
public:
    int rows;
    int columns;
    int dimension;
    Matrix();
    Matrix(int);
    Matrix(int, int);
    Matrix(std::initializer_list<std::initializer_list<int>>);
    ~Matrix();
    int operator()(int, int);
    const int get_determinant();
private:
    int* M;
    int laplace_expansion(Matrix&);
    const int plu_decomp();
};

#endif