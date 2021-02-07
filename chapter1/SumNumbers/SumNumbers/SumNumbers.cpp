// SumNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <stdio.h>
#include <iostream>

int SumNumbers(int a, ...);

template <typename ... T>
int SumNumbers2(T... args);

int main()
{
    int x = SumNumbers(3, 3, 4, 5);
    int x2 = SumNumbers2(3, 4, 5);
    std::cout << x << "\n";
    std::cout << x2 << "\n";
}

int SumNumbers(int count, ...)
{
    int sum = 0;
    va_list args = NULL;
    va_start(args, count);
    for (int i = 0; i < count; i++) 
    {
        int x = va_arg(args, int);
        sum += x;
    }
    va_end(args);
    return sum;
}

template <typename ... Args>
int SumNumbers2(Args... args)
{
    return (0 + ... + args);
}