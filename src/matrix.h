#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

class Matrix
{
public:
    int rows;
    int columns;
    int numElements;
    Matrix();
    Matrix(int);
    Matrix(int, int);
    Matrix(std::initializer_list<std::initializer_list<int>>);
    ~Matrix();
    int operator()(int, int);
    int get_determinant();
private:
    int* M;
    int laplace_expansion(Matrix&);
    int plu_decomp();
};

#endif