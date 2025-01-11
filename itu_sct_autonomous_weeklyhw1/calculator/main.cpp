#include <iostream>
#include "Calculator.h"

int main() {
    Calculator<double> calc;
    char operation;
    double num1, num2;

    std::cout << "Welcome to the Calculator!\n";
    while (true) {
        std::cout << "Enter an operation (+, -, *, /, s for square, ^ for exponentiation, % for modulus, or q to quit): ";
        std::cin >> operation;

        if (operation == 'q') break;

        try {
            if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
                std::cout << "Enter two numbers: ";
                std::cin >> num1 >> num2;

                if (std::cin.fail()) throw std::invalid_argument("Invalid input. Please enter numeric values.");

                switch (operation) {
                    case '+': std::cout << "Result: " << calc.addition(num1, num2) << "\n"; break;
                    case '-': std::cout << "Result: " << calc.subtraction(num1, num2) << "\n"; break;
                    case '*': std::cout << "Result: " << calc.multiplication(num1, num2) << "\n"; break;
                    case '/': std::cout << "Result: " << calc.division(num1, num2) << "\n"; break;
                }
            } else if (operation == 's') {
                std::cout << "Enter a number: ";
                std::cin >> num1;

                if (std::cin.fail()) throw std::invalid_argument("Invalid input. Please enter numeric values.");

                std::cout << "Result: " << calc.square(num1) << "\n";
            } else if (operation == '^') {
                int exp;
                std::cout << "Enter base and exponent (integer): ";
                std::cin >> num1 >> exp;

                if (std::cin.fail()) throw std::invalid_argument("Invalid input. Please enter numeric values.");

                std::cout << "Result: " << calc.exponentiation(num1, exp) << "\n";
            } else if (operation == '%') {
                int a, b;
                std::cout << "Enter two integers: ";
                std::cin >> a >> b;

                if (std::cin.fail()) throw std::invalid_argument("Invalid input. Please enter numeric values.");

                std::cout << "Result: " << calc.modulus(a, b) << "\n";
            } else {
                std::cout << "Invalid operation.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    std::cout << "Thank you for using the Calculator!\n";
    return 0;
}
