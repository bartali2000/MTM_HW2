#pragma once
#include <iostream>
using std::ostream;

class Matrix{
    int* matrix;
    int rows,columns;

public:
    //constuctors
    Matrix();
    Matrix(int rows, int columns, int num = 0);

    //copy constructor
    Matrix(const Matrix& other);

    //destructors
    ~Matrix();

    //operators
    int& operator()(const int& row,const int& column);
    Matrix& operator=(const Matrix& other);

    //printing operators
    friend ostream& operator<<(const ostream& os,const Matrix& other);

    //arithmetic operators
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const int& scalar);
    Matrix& operator-();
    Matrix operator*(const Matrix& other);

    //comparison operators
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);

};

Matrix operator+(const Matrix& a,const Matrix& b);
Matrix operator-(const Matrix& a,const Matrix& b);
Matrix operator*(const Matrix& a,const int scalar);
Matrix operator*(const int& scalar, const Matrix& a);

