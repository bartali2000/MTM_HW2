//
// Created by barak on 5/29/2025.
//
#include "Matrix.h"
#include "Utilities.h"
#include <iostream>
# include "math.h"
#include <string>
#include "MataMvidia.h"
using std::string;
using std::cout;
using std::endl;

// constructors
    MataMvidia ::MataMvidia(const std::string movie_name, const std::string creator, const Matrix *m,

                            const int frames_num){
    this->movie_name = movie_name;
    this->creator = creator;
    this->frames_num = frames_num;
    this->frames = new Matrix [this->frames_num];
    for (int i = 0; i < frames_num; ++i) {
        this->frames[i] = m[i];
        }
    }

    MataMvidia::MataMvidia() {
        this->frames_num = 0;
        this->frames = new Matrix[0];
    }

    // destructors
    MataMvidia::~MataMvidia() {
        delete [] this->frames;

    }

// copy constructors
    MataMvidia::MataMvidia(const MataMvidia& m){
    this->movie_name = m.movie_name;
    this->creator = m.creator;
    this->frames_num = m.frames_num;
    this->frames = new Matrix [this->frames_num];
    for (int i = 0; i < this->frames_num; ++i) {
        this->frames[i] = m.frames[i];
    }
}

// operator

    MataMvidia& MataMvidia ::operator=(const MataMvidia &m){
        this->movie_name = m.movie_name;
        this->creator = m.creator;
        this->frames_num = m.frames_num;
        delete [] this->frames;
        this->frames = new Matrix [this->frames_num];
        for (int i = 0; i < this->frames_num; ++i) {
            this->frames[i] = m.frames[i];
        }
        return *this;
    }

    Matrix& MataMvidia::operator[] (const int num_of_frame){
        return this->frames[num_of_frame];
    }

    const Matrix& MataMvidia::operator[] (const int num_of_frame)const{
        return this->frames[num_of_frame];
    }

    MataMvidia &MataMvidia::operator+=( const MataMvidia &m){
        /*Matrix* tmp = new Matrix [this->frames_num];
        for (int i = 0; i < this->frames_num; ++i) {
            tmp[i] = this->frames[i];
        }
        delete [] this->frames;
        int num_of_frames = this->frames_num;
        this->frames = new Matrix[this->frames_num+m.frames_num];
        for (int i = 0; i <num_of_frames ; ++i) {
            this->frames[i] = tmp [i];
        }
        for (int i = num_of_frames; i < num_of_frames + m.frames_num ; ++i) {
            this->frames[i] = m.frames[i-num_of_frames];
        }
        this->frames_num +=  m.frames_num;

        delete [] tmp;*/
        MataMvidia tmp = *this + m;
        *this = tmp;
        return *this;
    }

    MataMvidia & MataMvidia::operator+=( const Matrix &m){
        Matrix* tmp = new Matrix [this->frames_num+1];
        for (int i = 0; i < this->frames_num; ++i) {
            tmp[i] = this->frames[i];
        }
        tmp[this->frames_num ] = m;
        delete [] this->frames;
        this->frames_num ++;
        this->frames = tmp;
        //delete [] tmp;
        return *this;
    }

    MataMvidia MataMvidia:: operator+( const MataMvidia &m){
        //return (*this+=m);
        Matrix* tmp = new Matrix [this->frames_num + m.frames_num];
        for (int i = 0; i < this->frames_num; ++i) {
            tmp[i] = this->frames[i];
        }
        //delete [] this->frames;
        //int num_of_frames = this->frames_num;
        //this->frames = new Matrix[this->frames_num+m.frames_num];
        for (int i = this->frames_num; i < this->frames_num + m.frames_num; ++i) {
            tmp[i] = m.frames[i - this->frames_num];
        }
        MataMvidia n (this->movie_name, this->creator,tmp, this->frames_num + m.frames_num);
        delete [] tmp;
        return n;
    }



// print movie
    void MataMvidia::Print_movie(){
        cout << "Movie Name: "<< this->movie_name << endl;
        cout << "Author: "<< this->creator << endl;
        cout << endl;
        for (int i = 0; i < this->frames_num; ++i) {
        cout << "Frame " << i << ":" << endl;
        this->frames[i].Print_matrix();
        cout << endl;
        }
    }

    /*void MataMvidia::operator << (const MataMvidia &m){
        cout << "Movie Name: "<< m.movie_name << endl;
        cout << "Author: "<< m.creator << endl;
        cout << endl;
        for (int i = 0; i < m.frames_num; ++i) {
            cout << "Frame " << i << ":" << endl;
            m.frames[i].Print_matrix();
            cout << endl;
        }
    }*/
    std::ostream& operator<<(std::ostream& out, const MataMvidia& m) {
        out << "Movie Name: " << m.movie_name << endl;
        out << "Author: " << m.creator << endl;
        out << endl;
        for (int i = 0; i < m.frames_num; ++i) {
            out << "Frame " << i << ":" << endl;
            out<< m.frames[i];
            out << endl;
            if(i == m.frames_num - 1){
                out << "-----End of Movie-----"<< endl;
            }
        }
        return out;
    }
