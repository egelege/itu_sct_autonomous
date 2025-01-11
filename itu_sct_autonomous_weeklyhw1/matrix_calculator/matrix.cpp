#include "matrix.h"

namespace MatrixNamespace {

Matrix::Matrix(int rows, int cols, int initial) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<int>(cols, initial));
}

Matrix::Matrix(const std::vector<std::vector<int>>& values) : rows(values.size()), cols(values[0].size()) {
    data = values;
}

Matrix Matrix::zeros(int rows, int cols) {
    return Matrix(rows, cols, 0);
}

Matrix Matrix::identity(int size) {
    Matrix identity(size, size, 0);
    for (int i = 0; i < size; ++i) {
        identity.data[i][i] = 1;
    }

    return identity;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

int Matrix::trace() const {
    if (rows != cols) {
        throw std::invalid_argument("Trace is only defined for square matrices.");
    }
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += data[i][i];
    }
    return sum;
}

int Matrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant is only defined for square matrices.");
    }
    if (rows == 1) {
        return data[0][0];
    } else if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    } else if (rows == 3) {
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
             - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
             + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    } else {
        throw std::invalid_argument("Determinant is only supported for 1x1, 2x2, and 3x3 matrices.");
    }
}

void Matrix::inverse() const {
    if (rows != 3 || cols != 3) {
        throw std::invalid_argument("Inverse is only defined for 3x3 matrices.");
    }
    
    double det = static_cast<double>(determinant());
    if (det == 0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    Matrix result(3, 3);
    // int type kullandığımda 0 döndürüyor ve hatalı sonuç veriyordu static_Cast kullanarak bu sorunu çözebildik.
    double a = static_cast<double>(data[1][1]) * static_cast<double>(data[2][2]) - static_cast<double>(data[1][2]) * static_cast<double>(data[2][1]);
    double b = static_cast<double>(data[0][2]) * static_cast<double>(data[2][1]) - static_cast<double>(data[0][1]) * static_cast<double>(data[2][2]);
    double c= static_cast<double>(data[0][1]) * static_cast<double>(data[1][2]) - static_cast<double>(data[0][2]) * static_cast<double>(data[1][1]);
    double d = static_cast<double>(data[1][2]) * static_cast<double>(data[2][0]) - static_cast<double>(data[1][0]) * static_cast<double>(data[2][2]);
    double e = static_cast<double>(data[0][0]) * static_cast<double>(data[2][2]) - static_cast<double>(data[0][2]) * static_cast<double>(data[2][0]);
    double f = static_cast<double>(data[0][2]) * static_cast<double>(data[1][0]) - static_cast<double>(data[0][0]) * static_cast<double>(data[1][2]);
    double g = static_cast<double>(data[1][0]) * static_cast<double>(data[2][1]) - static_cast<double>(data[1][1]) * static_cast<double>(data[2][0]);
    double h = static_cast<double>(data[0][1]) * static_cast<double>(data[2][0]) - static_cast<double>(data[0][0]) * static_cast<double>(data[2][1]);
    double son = static_cast<double>(data[0][0]) * static_cast<double>(data[1][1]) - static_cast<double>(data[0][1]) * static_cast<double>(data[1][0]);
    std::vector<double> matr;
    matr.push_back(a);
    matr.push_back(b);
    matr.push_back(c);
    matr.push_back(d);
    matr.push_back(e);
    matr.push_back(f);
    matr.push_back(g);
    matr.push_back(h);
    matr.push_back(son);

    for (int i = 1; i < 10; ++i) {
        std::cout << matr.at(i-1)/det << " ";
        if(i % 3 == 0){
            std::cout << std::endl;
        }
    }

        std::cout << std::endl;
        std::cout << std::endl;
    
}

Matrix Matrix::dot(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for dot multiplication.");
    }
    Matrix result(rows, other.cols, 0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::add(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}
Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication!");
    }

    Matrix result(rows, other.cols, 0.0);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}


Matrix Matrix::neg() const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = -data[i][j];
        }
    }
    return result;
}

double Matrix::magnitude() const {
    double sum = 0.0;
    for (const auto& row : data) {
        for (const auto& element : row) {
            sum += element * element;
        }
    }
    return std::sqrt(sum);
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

} 