#include "Matrix.h"
#include <iostream>
#include <cmath>
#include "Utilities.h"
/*
 * here is a counter of the times I got cooked and didn't read the assignment correctly
 * counter: 5
*/



using std::cout , std::endl;

//constructors
Matrix::Matrix(): rows(0) , columns(0){
    matrix = new int[0];
}

Matrix::Matrix(int rows, int columns, int num): rows(rows), columns(columns){
    matrix = new int[rows*columns];
    for (int i = 0; i < rows*columns; ++i) {   //initialization of a matrix with a single number
        matrix[i] = num;
    }
}

// copy constructor

Matrix::Matrix(const Matrix& other){
    //create a new matrix
    int size = other.rows * other.columns;
    matrix = new int[size];
    rows = other.rows;
    columns = other.columns;
    // copying the data
    for (int i = 0; i < size; ++i) {
        this->matrix[i] = other.matrix[i];
    }
}

//destructor
Matrix::~Matrix(){
    delete[] this->matrix;
}

//operators
int& Matrix::operator()(const int &row, const int &col) {
    if(row < 0 || row >= rows || col < 0 || col >= columns){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return this->matrix[(row*columns) + col];
}

Matrix& Matrix::operator=(const Matrix& other){
    if (this == &other) {
        return *this;
    }
    delete[] this->matrix;
    this->matrix = new int[other.columns * other.rows];
    this->rows = other.rows;
    this->columns= other.columns;
    for (int i = 0; i < this->rows*this->columns; ++i) {
        this->matrix[i] = other.matrix[i];
    }
    return *this;
}


//printing operator
ostream& operator<<(const ostream& os,const Matrix& other){
    for (int i = 0; i < other.rows; i++) {
        cout << "|";
        for (int j = 0; j < other.columns; ++j) {
            cout << other.matrix[i*other.columns + j] << "|";
        }
        cout << endl;
    }
    return cout << endl;
}


// arithmetic operators
Matrix& Matrix::operator+=(const Matrix &other){
    if (this->rows != other.rows || this->columns != other.columns){
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < rows*columns; ++i) {
        this->matrix[i] += other.matrix[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &other) {
    if (this->columns != other.rows) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    int sumOfindex = 0;
    Matrix result = Matrix(this->rows, other.columns);

    for (int row = 0; row < this->rows; ++row) {
        for (int col = 0; col < other.columns; ++col) { // going to each index of the new matrix
            for (int curRow = 0; curRow < this->rows; ++curRow) {
                sumOfindex += this->matrix[row * this->columns + curRow] * other.matrix[other.columns * curRow + col];
            }
            result(row, col) = sumOfindex;
            sumOfindex = 0;
        }
    }
    return  *this = result;
}


Matrix Matrix::operator-() const {
    Matrix result(this->rows,this->columns,0);
    return result -= *this;
}


Matrix &Matrix::operator-=(const Matrix &other) {
    if (this->rows != other.rows || this->columns != other.columns) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < this->columns*this->rows; ++i) {
        this->matrix[i] -= other.matrix[i];
    }
    return *this;
}

Matrix &Matrix::operator*=(const int &scalar) {
    for (int i = 0; i < this->columns*this->rows; ++i) {
        this->matrix[i] *= scalar;
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const{
    Matrix result = *this;
    return result *= other;
}

bool Matrix::operator==(const Matrix &other) {
    if (this->rows != other.rows || this->columns != other.columns) {
        return false;
    }
    for (int i = 0; i < this->columns*this->rows; ++i) {
        if(this->matrix[i] != other.matrix[i]){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) {
    return !(*this == other);
}

Matrix operator+(const Matrix& a,const Matrix& b){
    Matrix tmp = a;
    return tmp += b;
}
Matrix operator-(const Matrix& a,const Matrix& b){
    Matrix tmp = a;
    return tmp -= b;
}

Matrix operator*(const Matrix& a,const int scalar){
    Matrix temp = a;
    temp *= scalar;
    return temp;
}
Matrix operator*(const int& scalar, const Matrix& a){
    return a*scalar;
}

