//
// Created by barak on 5/28/2025.
//

//#ifndef HW2_2425B_MATRIX_H
//#define HW2_2425B_MATRIX_H

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

    int &operator()(const int length, const int width);

    bool operator==(const Matrix &m);

    bool operator!=(const Matrix &m);

    Matrix &operator+(const Matrix &m);

    Matrix &operator-(const Matrix &m);

    Matrix &operator-();

    Matrix &operator*(const Matrix &m);

    Matrix &operator*(const int num);

    Matrix &operator*=(const Matrix &m);

    Matrix &operator*=(const int num);

    Matrix &operator-=(const Matrix &m);

    Matrix &operator+=(const Matrix &m);


    //print matrix
    void Print_matrix() const;


    // get function
    int get_width()const;

    int get_length()const;

    int get_value (const int i, const int j)const;

    //extra function
    Matrix &rotate_Clockwise();

    Matrix &rotate_Counter_Clockwise();

    Matrix Transpose();

    static double Calc_Frobenius_Norm( const Matrix &m);
};

    Matrix operator*(const int num, Matrix m);

//#endif //HW2_2425B_MATRIX_H
