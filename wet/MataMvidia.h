#pragma once
#include "Matrix.h"
#include <iostream>
#include <string>
using std::string;



class MataMvidia{
    string movieName;
    string creator;
    Matrix* movie = nullptr;
    int length = 0;

public:
    //constructors
    MataMvidia(const string& movieName,const string& creator,const Matrix* otherMovie,const int& length); //done
    MataMvidia(const MataMvidia& other); // done


    //destructor
    ~MataMvidia(); //done

    //operator
    MataMvidia& operator=(const MataMvidia& other); // done
    Matrix& operator[](const int index); //done
    Matrix& operator[](const int index) const; //done
    MataMvidia& operator+=(const MataMvidia& other); //done
    MataMvidia& operator+=(const Matrix& other); //done
    MataMvidia operator+(const MataMvidia& other) const; // done
    friend ostream& operator<<(ostream& os,const MataMvidia& other); // done
};