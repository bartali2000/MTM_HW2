#pragma once
#include <iostream>
using std::ostream;

class Matrix{
    int* array;
    int length,width;

public:
    //constuctors
    Matrix();
    Matrix(int length, int width, int num = 0);

    //copy constructor
    Matrix(const Matrix& matrix);

    //deconstructors
    ~Matrix();

    //operators
    int& operator()(const int& line,const int& row);
    Matrix& operator=(const Matrix& matrix);

    //printing operators
    friend ostream& operator<<(const ostream& os,const Matrix& matrix);

    //arithmetic operators
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    Matrix& operator*=(const int& scalar);
    Matrix& operator-();
    Matrix operator*(const Matrix& matrix);

    //comparison operators
    bool operator==(const Matrix& matrix);
    bool operator!=(const Matrix& matrix);

};

Matrix operator+(const Matrix& a,const Matrix& b);
Matrix operator-(const Matrix& a,const Matrix& b);
Matrix operator*(const Matrix& a,const int scalar);
Matrix operator*(const int& scalar, const Matrix& a);

