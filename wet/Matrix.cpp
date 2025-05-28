//
// Created by barak on 5/28/2025.
//

#include "Matrix.h"
#include "Utilities.h"
#include <iostream>
# include "math.h"

using std::cout;
using std::endl;
using std::sqrt;

// constructors
    Matrix::Matrix(const int length, const int width):length(length), width(width){
    this->matrix = new int[length * width];
    for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = 0;
    }
}

    Matrix:: Matrix(const int length, const int width, const int def_value):length(length), width(width){
    this->matrix = new int[length * width];
    for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = def_value;
    }
}

    Matrix::Matrix() {
    this->matrix = new int [0];
}

// destructors
    Matrix::~Matrix(){
    delete [] this->matrix;
}

//copy constructor

    Matrix::Matrix (const Matrix & matrix){
        this->length = matrix.length;
        this->width = matrix.width;
        this-> matrix = new int [this->length * this->width];
        for (int i = 0; i < matrix.length * matrix.width ; ++i) {
                this->matrix[i] = matrix.matrix[i];
        }
}

// operators

    Matrix& Matrix::operator= (const Matrix& m){
       //check size
       if (this->length != m.length ||  this->width != m.width){
           exitWithError(MatamErrorType:: UnmatchedSizes);
       }
       /* unrellevanty
        this->length = m.length;
        this->width = m.width;
        this-> matrix = new int [this->length * this->width];
        */
        for (int i = 0; i < m.length * m.width ; ++i) {
            this->matrix[i] = m.matrix[i];
        }
    return *this;
    }

    int& Matrix::operator() (const int length, const int  width){
        //check size
        if (this->length < length ||  this->width < width){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
       return this->matrix[(length * this->width) + width];
    }

    bool Matrix::operator==(const Matrix& m){
        //size
        if (this->length != m.length ||  this->width != m.width){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        // is equal?
        bool is_equal = true;
        for (int i = 0; i < this->length * this->width; ++i) {
            if(this->matrix[i] != m.matrix[i]){
                is_equal = false;
            }
        }
        return is_equal;
    }

    bool Matrix::operator!=(const Matrix& m){
        return !(*this == m);
    }

    Matrix& Matrix::operator+ (const Matrix& m){
        if (this->length != m.length ||  this->width != m.width){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        for (int i = 0; i < m.length * m.width ; ++i) {
            this->matrix[i] += m.matrix[i];
        }
        return *this;
    }

    Matrix& Matrix::operator-(const Matrix& m){
        if (this->length != m.length ||  this->width != m.width){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        for (int i = 0; i < m.length * m.width ; ++i) {
            this->matrix[i] -= m.matrix[i];
        }
        return *this;
    }

    Matrix& Matrix::operator-(){
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] = -this->matrix[i];
        }
        return *this;
    }

    Matrix& Matrix::operator*(const Matrix& m){
        if (this->width != m.length){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        Matrix mult(this->length, m.width);
        int sum = 0;
        int counter = 0;
        for (int c = 0; c < this->length ; ++c) {
            for (int i = 0; i < this->length; ++i) {
                for (int j = 0; j < this->width; ++j) {
                    sum += this->matrix[(c * this->width) + j] * m.matrix[(j * this->width) + c];
                }
                mult.matrix[counter] = sum;
                sum = 0;
                counter++;
            }
        }
        delete[] this->matrix;
        this->length = mult.length;
        this->width = mult.width;
        this->matrix = new int[this->length * this->width];
        for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = mult.matrix[i];
        }
        return *this;
    }

    Matrix& Matrix::operator*(const int num){
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] *= num;
        }
        return *this;
    }

    Matrix operator*(const int num, Matrix m){
        return (m * num);
    }

    Matrix& Matrix::operator*=(const Matrix& m){
      // the first try
        /*  Matrix result = (*this) * m;
        delete[] this->matrix;
        this->length = result.length;
        this->width = result.width;
        this->matrix = new int[length * width];
        for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = result.matrix[i];
        }*/
        return *this * m;
    }

    Matrix& Matrix::operator*=(const int num){
        return (*this*num);
    }

    Matrix& Matrix:: operator-=(const Matrix& m){
        return *this - m;
    }

    Matrix& Matrix::operator+=(const Matrix& m){
        return *this + m;
    }

    //print matrix

    void Matrix::Print_matrix()const{
    for (int i = 0; i < this->length; ++i) {
        for (int j = 0; j < this->width ; ++j) {
            if (j == 0){
                cout << "|";
            }
            cout << this->matrix[i* this->width + j] << "|";
            if(j == this-> width-1){
                cout << endl;
            }

        }
    }
    }

    // get functions

    int Matrix::get_width()const{
        return this->width;
    }

    int Matrix::get_length()const {
     return this->length;
    }

    int Matrix::get_value (const int i, const int j)const{
        return this->matrix[i * this->width + j];
    }


// extra function
    Matrix& Matrix:: rotate_Clockwise(){
        Matrix tmp(this->width, this->length);
        int count = 0;
        int index = 0;
        for (int j = this->length-1; j >= 0; --j) {
            for (int i = 0; i < tmp.length; ++i) {
                tmp.matrix[count * this->length+ index] = this->matrix[(j * this->width) + count];
                count++;
            }
            count = 0;
            index++;
        }
        delete[] this->matrix;
        this->length = tmp.length;
        this->width = tmp.width;
        this->matrix = new int[this->length * this->width];
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] = tmp.matrix[i];
        }
        return *this;
    }

   Matrix & Matrix::rotate_Counter_Clockwise(){
        Matrix tmp(this->width, this->length);
        int count = 0;
        int index = this->width-1;
        for (int j = 0; j < this->length; ++j) {
            for (int i = 0; i < this->length; ++i) {
                tmp.matrix[j * this->length + i] = this->matrix[(count * this->width) + index];
                count++;
            }
            count = 0;
            index--;
        }
        delete[] this->matrix;
        this->length = tmp.length;
        this->width = tmp.width;
        this->matrix = new int[this->length * this->width];
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] = tmp.matrix[i];
        }
        return *this;
    }

    Matrix Matrix::Transpose(){
        return this->rotate_Clockwise();
    }

    double Matrix::Calc_Frobenius_Norm(const Matrix &m){
        double sum = 0;
       for (int i = 0; i < m.get_length() ; ++i) {
           for (int j = 0; j < m.get_width(); ++j) {
               sum += m.get_value(i,j) * m.get_value(i,j);
           }
       }
        return sqrt(sum);
    }


