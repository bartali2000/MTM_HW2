#include "MataMvidia.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

// constructors
MataMvidia::MataMvidia(const string& movieName, const string& creator, const Matrix *otherMovie, const int& length) :
movieName(movieName),creator(creator),length(length){
    this->movie = new Matrix[length];
    for (int i = 0; i < this->length; ++i) {
        this->movie[i] = otherMovie[i];
    }
}
MataMvidia::MataMvidia(const MataMvidia &other) {
    this->movie = new Matrix[other.length];
    this->length = other.length;
    this->creator = other.creator;
    this->movieName = other.movieName;
    for (int i = 0; i < this->length; ++i) {
        this->movie[i] = other.movie[i];
    }
}

//destructor
MataMvidia::~MataMvidia() {
    delete[] this->movie;
}

// operators
MataMvidia &MataMvidia::operator=(const MataMvidia &other) {
    if(this == &other){
        return *this;
    }
    delete[] this->movie;
    this->movie = new Matrix[other.length];
    this->length = other.length;
    this->creator = other.creator;
    this->movieName = other.movieName;
    for (int i = 0; i < this->length; ++i) {
        this->movie[i] = other.movie[i];
    }
    return *this;
}


Matrix &MataMvidia::operator[](const int index) {
    return this->movie[index];
}

Matrix &MataMvidia::operator[](const int index) const {
    return this->movie[index];
}

MataMvidia &MataMvidia::operator+=(const Matrix &other) {
   const Matrix* tempMovie = &other;
   MataMvidia temp(this->movieName,this->creator,tempMovie,1);
   *this += temp;
   return *this;
}

MataMvidia &MataMvidia::operator+=(const MataMvidia &other) {
    if(other.length == 0 || other.movie == nullptr){
        return *this;
    }
    MataMvidia temp = *this;
    delete[] this->movie;
    this->movie = new Matrix[this->length + other.length];
    for (int i = 0; i < this->length; ++i) {
        this->movie[i] = temp.movie[i];
    }
    for (int i = 0; i < other.length; ++i) {
        this->movie[this->length + i] = other.movie[i];
    }
    this->length += other.length;
    return *this;
}

MataMvidia MataMvidia::operator+(const MataMvidia &other) const {
    MataMvidia result = *this;
    result += other;
    return result;
}
ostream& operator<<(ostream& os,const MataMvidia& other){
    os << "Movie Name: " << other.movieName << endl;
    os << "Author: " << other.creator << endl;
    for (int i = 0; i < other.length; ++i) {
        os << "Frame " << i << ':' << endl << other.movie[i] << endl;
    }
    return os;
}