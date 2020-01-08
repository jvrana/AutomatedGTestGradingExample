//
// ECEP520
//

#ifndef MYUTILS
#define MYUTILS
#include <map>
#include <vector>
#include "typed_matrix.h"
using std::vector;
using std::string;

// Question 1
vector<double> sort_by_magnitude(vector<double> &v);

// Question 2
// just refactor typed_matrix.h to use vector<vector<ElementType>>

// Question 3
TypedMatrix<double> read_matrix_csv(const string path);

// Question 4
void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);

// Question 5
std::map<string, int> occurrence_map(const string path);

string to_lower(string s);
string strip(string s);
bool is_valid_word(const string&);

#endif // MYUTILS