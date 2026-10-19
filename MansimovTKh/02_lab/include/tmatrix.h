// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) 
      throw out_of_range("Vector size should be less than or equal to 100000000");

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Vector size should be less than or equal to 100000000");
      if (arr == nullptr)
          throw invalid_argument("TDynamicVector ctor requires non-nullptr arg");
    //assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");

    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[v.sz];
      for (size_t i = 0; i < v.sz; i++) {
          this->pMem[i] = v.pMem[i];
      }

  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] this->pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      this->sz = v.sz;
      delete[] this->pMem;
      this->pMem = new T[this->sz];
      for (size_t i = 0; i < this->sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this==&v) return *this;

      delete[] pMem;
      this->sz = v.sz;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= this->sz) {
          throw out_of_range("Index out of range");
      }
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= this->sz) {
          throw out_of_range("Index out of range");
      }
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != this->sz) return false;
      for (size_t i = 0; i < v.sz; i++) {
          if (this->pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.size()) throw invalid_argument("The vector sizes must be equal");

      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] + v[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.size()) throw invalid_argument("The vector sizes must be equal");

      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] - v[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (this->sz != v.sz) throw invalid_argument("The vectors sizes must be equal");

      T res = T();
      for (size_t i = 0; i < this->sz; i++) {
          res += (this->pMem[i] * v[i]);
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};



// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s == 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size should be less than or equal to 10000");

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix& matrix) : TDynamicVector<TDynamicVector<T>>(matrix.size())
  {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = matrix[i];
      }
  }
  TDynamicMatrix(TDynamicMatrix&& matrix) : TDynamicVector<TDynamicVector<T>>(move(matrix)) 
  {
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  
  T& at(size_t i, size_t j) {
      if (i >= this->sz || j >= this->sz) throw out_of_range("Index out of range");
      return this->pMem[i][j];
  }
  const T& at(size_t i, size_t j) const {
      if (i>= this->sz || j >= this->sz) throw out_of_range("Index out of range");
      return this->pMem[i][j];
  }

  TDynamicMatrix& operator=(const TDynamicMatrix& matrix) {
      if (this == &matrix) return *this;
 
      delete[] this->pMem;
      
      this->sz = matrix.sz;
      this->pMem = new TDynamicVector<T>[this->sz];
      for (size_t i = 0; i < this->sz; i++) {
          this->pMem[i] = matrix[i];
      }

      return *this;
  }
  TDynamicMatrix& operator=(TDynamicMatrix&& matrix) noexcept {
      if (this == &matrix) return *this;

      delete[] this->pMem;
      this->sz = matrix.sz;
      this->pMem = matrix.pMem;

      matrix.pMem = nullptr;
      matrix.sz = 0;

      return *this;
      
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz) return false;
      for (size_t i = 0; i < this->sz; i++) {
          if (this->pMem[i] != m.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = this->pMem[i] * val;
      }

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->sz != v.size()) {
          throw invalid_argument("Number of columns of matrix must be equal to number of rows of vector");
      }
      TDynamicVector<T> res(v.size());
      T sum;
      for (size_t i = 0; i < this->sz;i++) {
          sum = T{};
          for (size_t j = 0; j < this->sz;j++) {
              sum += this->pMem[i][j] * v[j];
          }
          res[i] = sum;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
};

#endif
