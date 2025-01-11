

#include "matrix.h"
#include <iostream>
using namespace MatrixNamespace;

void showMenu() {
    std::cout << "\nMatrix Operations:\n";
    std::cout << "1. Create Zero Matrix\n";
    std::cout << "2. Create Identity Matrix\n";
    std::cout << "3. Transpose Matrix\n";
    std::cout << "4. Calculate Trace\n";
    std::cout << "5. Calculate Determinant\n";
    std::cout << "6. Calculate Inverse\n";
    std::cout << "7. Add Two Matrices\n";
    std::cout << "8. Subtract Two Matrices\n";
    std::cout << "9. Multiply Two Matrices\n";
    std::cout << "10. Negative Matrix\n";
    std::cout << "11. Magnitude of Matrix\n";
    std::cout << "12. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            Matrix m = Matrix::zeros(rows, cols);
            m.print();
            break;
        }
        case 2: {
            int size;
            std::cout << "Enter size: ";
            std::cin >> size;
            Matrix m = Matrix::identity(size);
            m.print();
            break;
        }
        case 3: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> values(rows, std::vector<int>(cols));
            std::cout << "Enter matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> values[i][j];
                }
            }
            Matrix m(values);
            Matrix t = m.transpose();
            t.print();
            break;
        }
        case 4: {
            int size;
            std::cout << "Enter size: ";
            std::cin >> size;
            std::vector<std::vector<int>> values(size, std::vector<int>(size));
            std::cout << "Enter matrix values:\n";
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cin >> values[i][j];
                }
            }
            Matrix m(values);
            std::cout << "Trace: " << m.trace() << "\n";
            break;
        }
           case 5: {
         int rows, cols;
            std::cout << "Enter rows and columns: ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> values(rows, std::vector<int>(cols));
    
            std::cout << "Enter matrix values:\n";
             for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                  std::cin >> values[i][j];
        }
    }

    Matrix m(values);
    std::cout << "Determinant: " << m.determinant() << "\n";
    break;
}

        case 6: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> values(rows, std::vector<int>(cols));
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> values[i][j];
                }
            }
            std::cout << "\n";

            Matrix m(values);
            try {
                m.inverse();
               // m.print();
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }
            break;
        }
        case 7: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> vals1(rows, std::vector<int>(cols));
            std::vector<std::vector<int>> vals2(rows, std::vector<int>(cols));
            std::cout << "Enter first matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> vals1[i][j];
                }
            }
            std::cout << "Enter second matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> vals2[i][j];
                }
            }

            Matrix m1(vals1);
            Matrix m2(vals2);
            Matrix result = m1.add(m2);
            std::cout << "Resultant Matrix (Addition):\n";
            result.print();
            break;
        }
        case 8: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> vals1(rows, std::vector<int>(cols));
            std::vector<std::vector<int>> vals2(rows, std::vector<int>(cols));
            std::cout << "Enter first matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> vals1[i][j];
                }
            }
            std::cout << "Enter second matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> vals2[i][j];
                }
            }

            Matrix m1(vals1);
            Matrix m2(vals2);
            Matrix result = m1.subtract(m2);
            std::cout << "Resultant Matrix (Subtraction):\n";
            result.print();
            break;
        }
        case 9: {
            int rows1, cols1, rows2, cols2;
            std::cout << "Enter rows and columns for first matrix: ";
            std::cin >> rows1 >> cols1;
            std::cout << "Enter rows and columns for second matrix: ";
            std::cin >> rows2 >> cols2;

            if (cols1 != rows2) {
                std::cout << "Matrix dimensions do not match for multiplication!\n";
                break;
            }

            std::vector<std::vector<int>> vals1(rows1, std::vector<int>(cols1));
            std::vector<std::vector<int>> vals2(rows2, std::vector<int>(cols2));
            std::cout << "Enter first matrix values:\n";
            for (int i = 0; i < rows1; ++i) {
                for (int j = 0; j < cols1; ++j) {
                    std::cin >> vals1[i][j];
                }
            }
            std::cout << "Enter second matrix values:\n";
            for (int i = 0; i < rows2; ++i) {
                for (int j = 0; j < cols2; ++j) {
                    std::cin >> vals2[i][j];
                }
            }

            Matrix m1(vals1);
            Matrix m2(vals2);
            try {
                Matrix result = m1.multiply(m2);
                std::cout << "Resultant Matrix (Multiplication):\n";
                result.print();
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }
            break;
        }
        
        case 10: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> values(rows, std::vector<int>(cols));
            std::cout << "Enter matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> values[i][j];
                }
            }
            Matrix m(values);
            Matrix neg = m.neg();
            neg.print();
            break;
        }
        case 11: {
            int rows, cols;
            std::cout << "Enter rows and columns:[],[] ";
            std::cin >> rows >> cols;
            std::vector<std::vector<int>> values(rows, std::vector<int>(cols));
            std::cout << "Enter matrix values:\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cin >> values[i][j];
                }
            }
            Matrix m(values);
            std::cout << "Magnitude: " << m.magnitude() << "\n";
            break;
        }
        case 12:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
