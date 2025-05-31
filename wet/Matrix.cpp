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
    if(length == 0 || width == 0){
        this->matrix = nullptr;
    }else{
    this->matrix = new int[length * width];
    for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = 0;
    }
    }
}

    Matrix:: Matrix(const int length, const int width, const int def_value):length(length), width(width){
        if(length == 0 || width == 0){
            this->matrix = nullptr;
        }else {
            this->matrix = new int[length * width];
            for (int i = 0; i < length * width; ++i) {
                this->matrix[i] = def_value;
            }

        }
}

    Matrix::Matrix() {
        this->width = 0;
        this->length = 0;
        this->matrix = nullptr;
}

// destructors
    Matrix::~Matrix(){
    delete [] this->matrix;
}

//copy constructor

    Matrix::Matrix (const Matrix & matrix){
        this->length = matrix.length;
        this->width = matrix.width;
        if(matrix.length == 0 || matrix.width == 0){
            this->matrix = nullptr;

        }else {
        this-> matrix = new int [this->length * this->width];
        for (int i = 0; i < matrix.length * matrix.width ; ++i) {
                this->matrix[i] = matrix.matrix[i];
        }
     }
}

// operators

    Matrix& Matrix::operator= (const Matrix& m){
       //check size - this is nessecary?
       /*if (this->length != m.length ||  this->width != m.width){
           exitWithError(MatamErrorType:: UnmatchedSizes);
       }*/
       /* unrellevant
        this->length = m.length;
        this->width = m.width;
        this-> matrix = new int [this->length * this->width];
        */

        delete [] this->matrix;
        this->width = m.width;
        this->length = m.length;
        if(m.length == 0 || m.width == 0){
            this->matrix = nullptr;
            return *this;
        }
        this->matrix = new int [m.length * m.width];
        for (int i = 0; i < m.length * m.width ; ++i) {
            this->matrix[i] = m.matrix[i];
        }
    return *this;
    }

    int &Matrix::operator() (const int length, const int  width){
        //check size
        if (this->length < length ||  this->width < width){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
       return this->matrix[(length * this->width) + width];
    }

    const int &Matrix::operator()(const int length, const int width)const{
        if (this->length < length ||  this->width < width){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
        if(this->length == 0 || this->width == 0){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
        return this->matrix[(length * this->width) + width];
    }

    bool Matrix::operator==(const Matrix& m){
        //size
        if (this->length != m.length ||  this->width != m.width){
            return false;
            //exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if(m.length == 0 || m.width == 0){
            return false;
            //exitWithError(MatamErrorType:: OutOfBounds);
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

    Matrix Matrix::operator+ (const Matrix& m){
        if((m.length == 0 || m.width == 0) && (this->length == 0 || this->width == 0)){
            return Matrix(0,0);/// add 0+0 do nothing
            //exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if(m.length == 0 || m.width == 0){
            Matrix a = Matrix(this->length, this->width);
            a = *this;
            return a;
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if (this->length != m.length ||  this->width != m.width){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }

        Matrix n(this->length, this->width);
        for (int i = 0; i < m.length * m.width ; ++i) {
            n.matrix[i] = this->matrix[i] + m.matrix[i];
        }
        return n;
    }

    Matrix& Matrix::operator-(const Matrix& m){
        if (this->length != m.length ||  this->width != m.width){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if((m.length == 0 || m.width == 0) && (this->length == 0 || this->width == 0)){
            return *this;/// add 0-0 do nothing
            //exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if(m.length == 0 || m.width == 0){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
        for (int i = 0; i < m.length * m.width ; ++i) {
            this->matrix[i] -= m.matrix[i];
        }
        return *this;
    }

    Matrix Matrix::operator-(){
        if(this->length == 0 || this->width == 0){
            return *this;
            //exitWithError(MatamErrorType:: OutOfBounds);
        }
        Matrix tmp(this->length, this->width);
        for (int i = 0; i < this->length * this->width; ++i) {
            tmp.matrix[i] = -this->matrix[i];
        }
        return tmp;
    }

    /*Matrix Matrix::operator*(const Matrix& m){
        if (this->width != m.length){
            exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if((m.length == 0 || m.width == 0) && (this->length == 0 || this->width == 0)){
            return *this;/// mult 0*0 do nothing
            //exitWithError(MatamErrorType:: UnmatchedSizes);
        }
        if(m.length == 0 || m.width == 0 || this->length == 00 || this->width == 0){
            return *this;
            //exitWithError(MatamErrorType:: OutOfBounds);
        }
        Matrix mult(this->length, m.width);
       // int sum = 0;
        int counter = 0;
        for (int c = 0; c < this->length ; ++c) {
            for (int i = 0; i < m.width; ++i) {
                int sum = 0;
                for (int j = 0; j < this->width; ++j) {
                    //sum += this->matrix[(c * this->width) + j] * m.matrix[(j * this->width) + i];
                    sum += this->matrix[c * this->width + j] * m.matrix[j * m.width + i];
                }
                mult.matrix[c * m.width + i] = sum;
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
        return mult;
    }*/

    Matrix Matrix::operator*(const Matrix& m) {
    if (this->width != m.length) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->length, m.width);
    for (int i = 0; i < this->length; ++i) {
        for (int j = 0; j < m.width; ++j) {
            int sum = 0;
            for (int k = 0; k < this->width; ++k) {
                sum += this->matrix[i * this->width + k] * m.matrix[k * m.width + j];
            }
            result.matrix[i * m.width + j] = sum;
        }
    }
    return result;
}

    Matrix Matrix::operator*(const int num){
        if(this->length == 0 || this->width == 0){
            exitWithError(MatamErrorType:: OutOfBounds);
        }
        Matrix tmp(this->length, this->width);
        for (int i = 0; i < this->length * this->width; ++i) {
           tmp.matrix[i] = this->matrix[i] * num;
        }
        return tmp;
    }

    Matrix operator*(const int num, Matrix m){
        return (m * num);
    }

    Matrix & Matrix::operator*=(const Matrix& m){
      // the first try
        /*  Matrix result = (*this) * m;
        delete[] this->matrix;
        this->length = result.length;
        this->width = result.width;
        this->matrix = new int[length * width];
        for (int i = 0; i < length * width; ++i) {
            this->matrix[i] = result.matrix[i];
        }*/
        Matrix tmp = *this * m;
        *this = tmp;
        return *this;
    }

    Matrix Matrix::operator*=(const int num){
        Matrix tmp = *this * num;
        *this = tmp;
        return *this;

    }

    Matrix& Matrix:: operator-=(const Matrix& m){
        return *this - m;
    }

    Matrix Matrix::operator+=(const Matrix& m){
        Matrix tmp = *this + m;
        *this = tmp;
        return *this;
        //return *this + m;
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

  /*  void Matrix::operator<<(Matrix &m){
        for (int i = 0; i < m.length; ++i) {
            for (int j = 0; j < m.length; ++j) {
                if (j == 0){
                    cout << "|";
                }
                cout << m.matrix[i* m.width + j] << "|";
                if(j == m.width - 1){
                    cout << endl;
                }
            }
        }
    }*/
  /* std::ostream& operator<<(Matrix m){
      std::ostream &print = std::cout;
       for (int i = 0; i < m.length; ++i) {
           for (int j = 0; j < m.length; ++j) {
               if (j == 0) {
                   print << "|";
               }
               print << m.matrix[i * m.width + j] << "|";
               if (j == m.width - 1) {
                   print << endl;
               }
           }
       }
      return print;
   }*/

    std::ostream& operator<<(std::ostream& out, const Matrix& m) {
      if (m.matrix == nullptr && m.length == 0 && m.width == 0) {
         // out<< "" << std::endl;
          return out;
      }
      if (m.matrix == nullptr || m.length == 0 || m.width == 0) {
          //out<< "" << std::endl;
          return out;
      }
      for (int i = 0; i < m.length; ++i) {
          for (int j = 0; j < m.width; ++j) {
              if (j == 0) {
                  out << "|";
              }
              if (j == m.width - 1/* && i != m.length - 1*/) {
                  out << m.matrix[i * m.width + j] << "|"<< endl;                 // return out;
              } else{
                  out << m.matrix[i * m.width + j] << "|";
              }
          }
         /* if (i != m.length - 1 ) {
              out << endl;
          }*/
      }
      return out;
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
    Matrix Matrix:: rotateClockwise(){
        if (this->matrix == nullptr || this->length == 0 || this->width == 0){
            return *this;
        }
        Matrix tmp(this->width, this->length);
        int count = 0;
        int index = 0;
        for (int j = this->length-1; j >= 0; --j) {
            for (int i = 0; i < tmp.width; ++i) {
                tmp.matrix[count * this->length+ index] = this->matrix[(j * this->width) + count];
                count++;
            }
            count = 0;
            index++;
        }
        /*delete[] this->matrix;
        this->length = tmp.length;
        this->width = tmp.width;
        this->matrix = new int[this->length * this->width];
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] = tmp.matrix[i];
        }*/
        return tmp;
    }

   Matrix Matrix::rotateCounterClockwise(){
       if (this->matrix == nullptr || this->length == 0 || this->width == 0){
           return *this;
       }
        Matrix tmp(this->width, this->length);
        int count = 0;
        int index = this->width-1;
        for (int j = 0; j < this->length; ++j) {
            for (int i = 0; i < this->width; ++i) {
               // tmp.matrix[j * this->length + i] = this->matrix[(count * this->width) + index];
                tmp.matrix[(this->width - 1 - i) * this->length + j] = this->matrix[j * this->width + i];
                count++;
            }
            count = 0;
            index--;
        }
        /*delete[] this->matrix;
        this->length = tmp.length;
        this->width = tmp.width;
        this->matrix = new int[this->length * this->width];
        for (int i = 0; i < this->length * this->width; ++i) {
            this->matrix[i] = tmp.matrix[i];
        }*/
        return tmp;
    }

    Matrix Matrix::transpose(){
        if (this->matrix == nullptr || this->length == 0 || this->width == 0){
            return *this;
        }
        Matrix tmp(this->width, this->length);
        int index = 0;
        for (int i = 0; i < this->length; ++i) {
            for (int j = 0; j < this->width; ++j) {
                tmp.matrix[(j * this->length) +index] = this->matrix[i* this->width+j];
            }
            index++;
        }
        return tmp;
    }

    double Matrix::Calc_Frobenius_Norm(const Matrix &m){
        if(m.width == 0 || m.length == 0 || m.matrix == nullptr){
            return 0;
        }
        double sum = 0;
       for (int i = 0; i < m.length ; ++i) {
           for (int j = 0; j < m.width; ++j) {
               sum += m(i,j) * m(i,j);
           }
       }
        return sqrt(sum);
    }


