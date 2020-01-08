//
// Created by KlavinsLab on 2019-02-14.
//

#ifndef ECE590_TYPED_MATRIX_H
#define ECE590_TYPED_MATRIX_H

#ifndef TYPEDMATRIX_H
#define TYPEDMATRIX_H

#include <vector>
#include <stdexcept>
#include <iostream>

using std::vector;
using std::string;


template <typename T>
class TypedMatrix {

public:
    TypedMatrix();
    TypedMatrix(int m, int n);
    TypedMatrix(const TypedMatrix& other);

    ~TypedMatrix();

    //getter
    const T& get(int i, int j) const;

    int rows() const;
    int cols() const;

    //setter
    void set(int i, int j, T value);

    // operator
    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator-=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other) const;
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    // HW5
    static TypedMatrix<double> read_matrix_csv(const string path);
    static void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);

    // utility
    TypedMatrix<T>& resize(int m, int n);
    TypedMatrix<T>& add_row();
    TypedMatrix<T>& add_col();
    bool same_shape(const TypedMatrix& other) const;
    void check_shape(const TypedMatrix& other) const;

private:
    int rows_;
    int cols_;
    vector<vector<T>> mat;
};

/*
 * Default constructor
 */
template <typename T>
TypedMatrix<T>::TypedMatrix(){
    mat.resize(1);
    mat[0].resize(1, T());
    rows_ = 1;
    cols_ = 1;
}

/*
 * Constructor
 */
template <typename T>
TypedMatrix<T>::TypedMatrix(int m, int n){
    mat.resize(m);

    // columns, with initial value
    typename vector<vector<T>>::iterator row;
    typename vector<T>::iterator col;
    for (row = mat.begin() ; row != mat.end(); ++row) {
        (*row).resize(n);
        for (int j = 0; j < n; j++) {
            (*row).push_back(T());
        }
    }
    rows_ = m;
    cols_ = n;
}

template <typename T>
TypedMatrix<T>::TypedMatrix(const TypedMatrix& other) : TypedMatrix() {
    *this = other;
}

// Destructor
template <typename T>
TypedMatrix<T>::~TypedMatrix() {
    mat.clear();
}

/*
 * Number of columns
 */
template <typename T>
int TypedMatrix<T>::cols() const{
    return this->cols_;
}

/*
 * Number of rows
 */
template <typename T>
int TypedMatrix<T>::rows() const{
    return this->rows_;
}

/*
 * Get the i-th and j-th element
 */
template <typename T>
const T&  TypedMatrix<T>::get(int i, int j) const{
    if (i< 0 || i>=rows_ || j<0 || j>=cols_ ) {
        throw std::range_error("Out of range index in matrix");
    }
    return this->mat[i][j];
}

template <typename T>
bool TypedMatrix<T>::same_shape(const TypedMatrix<T>& other) const {
    if ( (this->cols_!=other.cols()) || this->rows_!=other.rows() ){
        return false;
    }
    return true;
}

template <typename T>
void TypedMatrix<T>::check_shape(const TypedMatrix<T> &other) const {
    if (!same_shape(other)) {
        throw std::range_error("Out of range index in matrix");
    }
    return;
}

/*
 * Set the i-th and j-th element
 */
template <typename T>
void TypedMatrix<T>::set(int i, int j, T val){
    if (i< 0 || i>=rows_ || j<0 || j>=cols_ ) {
        throw std::range_error("Out of range index in matrix");
    }
    this->mat[i][j] = val;
}

/*
 * Utility method for resizing the entire matrix
 */
template <typename T>
TypedMatrix<T>& TypedMatrix<T>::resize(int m, int n) {
    mat.resize(m);
    for (int i = 0; i < m; i++) {
        mat[i].resize(n);
    }
    rows_ = m;
    cols_ = n;
    return *this;
}

template <typename T>
TypedMatrix<T>& TypedMatrix<T>::operator=(const TypedMatrix<T>& other){
    resize(other.rows(), other.cols());
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            set(i, j, other.get(i, j));
        }
    }

    return *this;
}

template <typename T>
TypedMatrix<T>& TypedMatrix<T>::operator+=(const TypedMatrix<T>& other){
    if ( (cols()!=other.cols_) || (rows()!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            set(i, j, other.get(i, j) + get(i, j));
        }
    }
    return *this;
}

template <typename T>
TypedMatrix<T>& TypedMatrix<T>::operator*=(const TypedMatrix<T>& other){
    if ( (cols()!=other.cols_) || (rows()!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            set(i, j, other.get(i, j) * get(i, j));
        }
    }
    return *this;
}

template <typename T>
TypedMatrix<T>& TypedMatrix<T>::operator-=(const TypedMatrix<T>& other){
    this->resize(other.rows(), other.cols());
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            this->set(i, j, this.get(i, j) - other.get(i, j));
        }
    }

    return *this;
}

template <typename T>
bool TypedMatrix<T>::operator==(const TypedMatrix<T>& other) const{
    if ( (cols_!=other.cols_) || (rows_!=other.rows_) ){
        return false;
    }
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<this->cols_; j++){
            if(get(i,j) != other.get(i,j))
                return false;
        }
    }
    return true;
}


template <typename T>
TypedMatrix<T> TypedMatrix<T>::operator+(const TypedMatrix<T>& other){
    if ( (cols()!=other.cols_) || (rows()!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    }
    TypedMatrix<T> m(rows(), cols());
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            m.set(i, j, other.get(i, j) + get(i, j));
        }
    }
    return m;
}

template <typename T>
TypedMatrix<T> TypedMatrix<T>::operator*(const TypedMatrix<T>& other){

    // for matrix multiplication, a 'm x n' and a 'n x p' makes a 'm x p'
    if (cols_!=other.rows_){
        throw std::range_error("Matrix dimension doesn't match.");
    } else if (rows_ == 0 || cols_ == 0 || other.rows_ == 0 || other.cols_ == 0) {
        throw std::range_error("Missing rows or colums");
    }
    TypedMatrix<T> prod(rows_, other.cols_);

    for (int i=0; i<rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            T tmp = T();
            for (int k=0; k<cols_; k++) {
                tmp = tmp + get(i, k) * other.get(k, j);
            }
            prod.set(i, j, tmp);
        }
    }

    return prod;
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedMatrix<ElementType> &matrix)
{
    os << '[';
    for(int i=0; i<matrix.rows(); i++){
        if (i>0)
            os << ' ';
        os << '[';
        for(int j=0; j<matrix.cols(); j++){
            os << matrix.get(i, j);
            if (j<matrix.cols()-1){
                os << ",";
            }
        }
        os << ']';
        if (i<matrix.rows()-1)
            os << '\n';
    }
    os << ']';
    return os;
}

#endif

#endif //ECE590_TYPED_MATRIX_H
