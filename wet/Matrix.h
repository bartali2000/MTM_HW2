#pragma once
#include <iostream>
using std::ostream;

class Matrix{
    int* matrix;
    int rows,columns;

    // helper function
    static int CalcSmallerDeterminant(const Matrix& mat, int row, int col) ;
public:
    //constuctors
    Matrix();
    Matrix(int rows, int columns, int num = 0); //done

    //copy constructor
    Matrix(const Matrix& other); // done

    //destructors
    ~Matrix(); // done

    //operators
    int& operator()(const int& row,const int& column); // done
    int& operator()(const int& row,const int& column) const;

    Matrix& operator=(const Matrix& other); // done

    //printing operators
    friend ostream& operator<<(const ostream& os,const Matrix& other); // done

    //arithmetic operators
    Matrix& operator+=(const Matrix& other); // done
    Matrix& operator-=(const Matrix& other); // done
    Matrix& operator*=(const Matrix& other); // done
    Matrix& operator*=(const int& scalar); // done
    Matrix operator-() const; // done;
    Matrix operator*(const Matrix& other) const; // done

    //comparison operators
    bool operator==(const Matrix& other); // done
    bool operator!=(const Matrix& other); // done

    // additional required functions
    Matrix rotateClockwise(); //done
    Matrix rotateCounterClockwise(); //done
    Matrix transpose(); // done
    static double CalcFrobeniusNorm(const Matrix& a);
    static int CalcDeterminant(const Matrix& a);
};

Matrix operator+(const Matrix& a,const Matrix& b); // done
Matrix operator-(const Matrix& a,const Matrix& b); //done
Matrix operator*(const Matrix& a,const int scalar); //done
Matrix operator*(const int& scalar, const Matrix& a);// done

