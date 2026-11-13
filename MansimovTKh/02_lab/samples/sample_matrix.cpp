// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
    TDynamicMatrix<int> a(5), b(5), c(5);
    TDynamicVector<int> v1(4), v2(4), v3(4);
    TDynamicVector<int> v4(5);
    int scalar = 5;

    setlocale(LC_ALL, "Russian");
    cout << "-----Тестирование класса работы с векторами-----"
        << endl << endl;
    cout << "ВЕКТОРНЫЕ ОПЕРАЦИИ"
        << endl;
    v1[0] = 10; v1[1] = 20; v1[2] = 30; v1[3] = 40;
    v2[0] = 2; v2[1] = 4; v2[2] = 6; v2[3] = 8;

    v3 = v1 + v2;
    cout << "Vector v1 = [ " << v1 << "]" << endl;
    cout << "Vector v2 = [ " << v2 << "]" << endl << endl;
    cout << "Vector v3 = v1 + v2 = [ " << v3 << "]" << endl << endl;

    v3 = v1 - v2;
    cout << "Vector v3 = v1 - v2 = [ " << v3 << "]" << endl << endl;

    cout << "СКАЛЯРНЫЕ ОПЕРАЦИИ" << endl;
    v3 = v1 + 5;
    cout << "Vector v3 = v1 + 5 = [ " << v3 << "]" << endl << endl;
    v3 = v1 - 5;
    cout << "Vector v3 = v1 - 5 = [ " << v3 << "]" << endl << endl;
    v3 = v1 * 5;
    cout << "Vector v3 = v1 * 5 = [ " << v3 << "]" << endl << endl;


    cout << "-----Тестирование класса работы с матрицами-----"
        << endl;
    a[0][0] = 0; a[0][1] = 1; a[0][2] = 2; a[0][3] = 3; a[0][4] = 4;
    a[1][0] = 10; a[1][1] = 11; a[1][2] = 12; a[1][3] = 13;
    a[2][0] = 20; a[2][1] = 21; a[2][2] = 22;
    a[3][0] = 30; a[3][1] = 31;
    a[4][0] = 40;

    b[0][0] = 0; b[0][1] = 100; b[0][2] = 200; b[0][3] = 300; b[0][4] = 400;
    b[1][0] = 1000; b[1][1] = 1100; b[1][2] = 1200; b[1][3] = 1300;
    b[2][0] = 2000; b[2][1] = 2100; b[2][2] = 2200;
    b[3][0] = 3000; b[3][1] = 3100;
    b[4][0] = 4000;

    v4[0] = 1; v4[1] = 2; v4[2] = 3; v4[3] = -1; v4[4] = -2;

    cout << "МАТРИЧНО-ВЕКТОРНЫЕ ОПЕРАЦИИ" << endl;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Vector v4 = [ " << v4 << "]" << endl << endl;

    v3 = a * v4;
    cout << "Vector v3 = a * v4 = [ " << v3 <<"]"<< endl << endl;

  cout << "МАТРИЧНО-МАТРИЧНЫЕ ОПЕРАЦИИ" << endl;
  c = a + b;
  cout << "Matrix c = a + b" << endl << c << endl<<endl;
  c = a - b;
  cout << "Matrix c = a - b" << endl << c << endl<<endl;
  c = a * b;
  cout << "Matrix c = a * b" << endl << c << endl << endl;

}
//---------------------------------------------------------------------------
