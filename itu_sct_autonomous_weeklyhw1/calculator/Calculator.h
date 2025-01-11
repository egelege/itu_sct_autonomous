#ifndef CALCULATOR_H
#define CALCULATOR_H

template <typename T>
class Calculator {
public:
    T addition(T a, T b);
    T subtraction(T a, T b);
    T multiplication(T a, T b);
    T division(T a, T b);
    T square(T a);
    T exponentiation(T base, int exp);
    T modulus(int a, int b); // Modulus works only for integers
};

#endif
