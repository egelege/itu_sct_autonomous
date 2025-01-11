#include "Calculator.h"
#include <stdexcept>
#include <cmath>

template <typename T>
T Calculator<T>::addition(T a, T b) {
    return a + b;
}

template <typename T>
T Calculator<T>::subtraction(T a, T b) {
    return a - b;
}

template <typename T>
T Calculator<T>::multiplication(T a, T b) {
    return a * b;
}

template <typename T>
T Calculator<T>::division(T a, T b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}

template <typename T>
T Calculator<T>::square(T a) {
    return a * a;
}

template <typename T>
T Calculator<T>::exponentiation(T base, int exp) {
    return std::pow(base, exp);
}

template <typename T>
T Calculator<T>::modulus(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Modulus by zero is not allowed.");
    }
    return a % b;
}

template class Calculator<double>;
template class Calculator<int>;
