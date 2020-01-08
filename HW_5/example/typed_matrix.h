//
// Created by KlavinsLab on 2019-02-14.
//

#ifndef TYPEDMATRIX_H
#define TYPEDMATRIX_H

#include <vector>
#include <stdexcept>
using std::vector;
using std::string;

/*
 * You code should look pretty similar to HW_4, but conveniently, you'll
 * get to use the vector<vector<ElementType>> type, which is WAY easier to
 * use.
 *
 * Note that we are implementing the read and write csv methods
 * as a static method inside the TypedMatrix. We can call it
 * in our tests via TypdeMatrix<double>::read_matrix_csv or
 * TypedMatrix<double>::write_matrix_csv
 */

template <typename ElementType>
class TypedMatrix {

public:
    // refactor previous code to use the std::vector class
    // see private variable 'matrix' below as an example of the
    // type you'll be using

    TypedMatrix();
    TypedMatrix(int n, int m);
    TypedMatrix(const TypedMatrix& other);

    ~TypedMatrix();

    //getter
    const ElementType& get(int i, int j) const;
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

    /*
     * If you were to implement static functions for write_matrix_csv and
     * read_matrix_csv, it'd be done as in commented code below. The function definition
     * would be specified in typed_matrix.cc. Please see the typed_matrix.cc.example
     * file as an example of how you would define the functions.
     */
    /*
        static TypedMatrix<double> TypedMatrix<double>::read_matrix_csv(const string path);
        static void TypedMatrix<double>::write_matrix_csv(const TypedMatrix<double> &matrix, const string path);
     */

private:
    int rows_;
    int cols_;
    vector< vector<ElementType> > matrix; // < you can call 'matrix' whatever, we don't care,
                                           // we can't access it because its private
};

// template methods implementations go here

#endif
