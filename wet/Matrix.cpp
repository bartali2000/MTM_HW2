#include "Matrix.h"
#include <iostream>
#include <cmath>
#include "Utilities.h"
/*
 * here is a counter of the times I was retarded
 * retard counter:9
 *
 * the time i started working on the Accursed Determinant function
 * stat time: 11:30
 * finish time: 12:42
 *
 *
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
int& Matrix::operator()(const int &row, const int &col) const{
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

Matrix Matrix::rotateClockwise() {
    Matrix rotated(this->columns,this->rows);
    for (int row = 0; row < this->rows; ++row) {
        for (int col = 0; col < this->columns; ++col) {
            rotated(col,rotated.columns -row -1) = (*this)(row,col);
        }
    }
    return rotated;
}
Matrix Matrix::rotateCounterClockwise() {
    Matrix rotated = *this;
    for (int i = 0; i < 3; ++i) {
        rotated = rotated.rotateClockwise();
    }
    return rotated;
}

Matrix Matrix::transpose() {
    Matrix transposed(this->columns,this->rows);
    for (int row = 0; row < this->rows; ++row) {
        for (int col = 0; col < this->columns; ++col) {
            transposed(col,row) = (*this)(row,col);
        }
    }
    return transposed;
}

double Matrix::CalcFrobeniusNorm(const Matrix &a) {
    double sum = 0;
    for (int i = 0; i < a.rows* a.columns; ++i) {
        sum += (a.matrix[i])*(a.matrix[i]);
    }
    return sqrt(sum);
}

int Matrix::CalcDeterminant(const Matrix &a) {
    if(a.columns != a.rows){
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    if (a.columns == a.rows && a.rows == 1){
        return a(0,0);
    }
    if(a.rows == 0 || a.columns == 0){
        return 0;
    }
    return Matrix::CalcSmallerDeterminant(a,0,0);
}

int Matrix::CalcSmallerDeterminant(const Matrix& mat, int row, int col) {
    if (mat.columns == 2 && mat.rows == 2) {
        return (mat(0, 0) * mat(1, 1) - mat(1, 0) * mat(0, 1));
    }

    int det = 0;
    for (int curCol = 0; curCol < mat.columns; ++curCol) { // going over the first row
        int sign = (curCol % 2 == 1) ? -1 : 1;
        //build smaller matrix====================================================
        Matrix smallerOne(mat.rows - 1, mat.columns - 1);
        int smallerIndex = 0;
        for (int matRow = 1; matRow < mat.rows; ++matRow) {  // i dont need to go over the first row because i develop for it
            for (int matCol = 0; matCol < mat.columns; ++matCol) {
                if (matCol != curCol) {
                    smallerOne.matrix[smallerIndex] = mat(matRow, matCol);
                    smallerIndex++;
                }
            }
        }
        // ===================================================================================
        det += sign* mat(0,curCol)*Matrix::CalcSmallerDeterminant(smallerOne,0,0);
    }
    return det;
}


/*
    * Explanation of my indexes:
    *
    * row and col are the indexes of the element of which im in right now
    * ee
    * curCol is the index in the first row of the matrix i currently have to calculate its det
    *
    * smallerOne is the smaller matrix....
    *
    * smaller index is the index in the array of the smaller matrix which is filled with the elements that are
    * not in the row and the col of the element i got
    *
    *
    */

int main(){
    Matrix m1(4,4);

    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(0,2) = 3;
    m1(0,3) = 4;
    m1(1,0) = 22;
    m1(1,1) = 2;
    m1(1,2) = 37;
    m1(1,3) = 6;
    m1(2,0) = 7;
    m1(2,1) = 5;
    m1(2,2) = 2;
    m1(2,3) = 7;
    m1(3,0) = 4;
    m1(3,1) = 3;
    m1(3,2) = 9;
    m1(3,3) = 8;


    cout << m1;
    cout << Matrix::CalcDeterminant(m1);

}
