//
// Created by barak on 5/28/2025.
//

//#ifndef HW2_2425B_MATRIX_H
//#define HW2_2425B_MATRIX_H
#include <string>

#pragma once

class Matrix {
    int *matrix;
    int length;
    int width;

public:
    // constructors
    Matrix(const int length, const int width);

    Matrix(const int length, const int width, const int def_value);

    Matrix();

    // destructors
    ~Matrix();

    // copy constructor
    Matrix(const Matrix &matrix);

    // operators

    Matrix &operator=(const Matrix &m);

    int & operator()(const int length, const int width);

    const int &operator()(const int length, const int width)const;

    bool operator==(const Matrix &m);

    bool operator!=(const Matrix &m);

    Matrix operator+(const Matrix &m);

    Matrix &operator-(const Matrix &m);

    Matrix operator-();

    Matrix operator*(const Matrix &m);

    Matrix operator*(const int num);

    Matrix & operator*=(const Matrix &m);

    Matrix operator*=(const int num);

    Matrix &operator-=(const Matrix &m);

    Matrix operator+=(const Matrix &m);


    //void operator<<(Matrix &m);

   // friend std::ostream& operator <<(Matrix m);
   friend std::ostream& operator<<(std::ostream& out, const Matrix& m);


    //extra function
    Matrix rotateClockwise();

    Matrix rotateCounterClockwise();

    Matrix transpose();

    static double Calc_Frobenius_Norm( const Matrix &m);
};

    Matrix operator*(const int num, Matrix m);



//#endif //HW2_2425B_MATRIX_H
