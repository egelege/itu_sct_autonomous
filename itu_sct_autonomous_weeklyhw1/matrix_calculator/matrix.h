#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace MatrixNamespace {

class Matrix {
private:
    std::vector<std::vector<int>> data;
    //std::vector<std::vector<double>> data_double;
    int rows, cols;

public:
    Matrix(int rows, int cols, int initial = 0);
    Matrix(const std::vector<std::vector<int>>& values);
    
   // double matrix (const std::vector<std::vector<double>>& matr);


    Matrix transpose() const;
    int trace() const;
    int determinant() const;
    void inverse() const;

    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    Matrix dot(const Matrix& other) const;
    Matrix neg() const;
    double magnitude() const;

    static Matrix zeros(int rows, int cols);
    static Matrix identity(int size);

    void print() const;
};

}
#endif
