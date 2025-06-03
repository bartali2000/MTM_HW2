//
// Created by barak on 5/29/2025.

#pragma once
#include "Matrix.h"
#include <string>
using std::string;

class MataMvidia{

    int frames_num;
    Matrix* frames;
    string movie_name;
    string creator;

public:
    // constructors
    MataMvidia(const string movie_name, const string creator, const Matrix* m, const int  frames_num);

    MataMvidia();

    // destructors
    ~MataMvidia();

    // copy constructors
    MataMvidia(const MataMvidia& m);

    // operators
    MataMvidia &operator=(const MataMvidia &m);

    Matrix &operator[] (const int num_of_frame);

    const Matrix &operator[] (const int num_of_frame)const;

    MataMvidia & operator+=( const MataMvidia &m);

    MataMvidia & operator+=( const Matrix &m);

    MataMvidia  operator+( const MataMvidia &m);
/*
    // print movie
     void Print_movie();
*/
    //void operator << (const MataMvidia &m);

    friend std::ostream& operator<<(std::ostream& out, const MataMvidia& m);

};