//
// Created by barak on 5/28/2025.
//
#include "Matrix.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

 int main (){
     Matrix n(3,3,1);
    /* n(16,0) = 5;
     n(15,1) = 0;
     n(0,0) = 0;*/
     n.Print_matrix();
     double v = Matrix::Calc_Frobenius_Norm(n);
     cout << v;
    /* Matrix tr = n.Transpose();
     tr.Print_matrix();*/
     /*Matrix m (3,4,4);
     n *=3;
     n.Print_matrix();
     cout<< endl;
     n.rotate_Counter_Clockwise();
     n.Print_matrix();
     cout<< endl;
     //n *= m;
   //  n(1,2) = 3;
     //n *= m;
     //n.Print_matrix();*/

     return 0;
 }