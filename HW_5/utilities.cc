#include "utilities.h"
#include <algorithm>
#include <fstream>      // std::fstream
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>


using std::vector;
using std::string;

bool sort_by_abs(double i, double j) {
    return fabs(i) < fabs(j);
}

vector<double> sort_by_magnitude(vector<double> &x) {
    // add your code here for question HW5.1
    vector<double> v = x;
    std::sort(v.begin(), v.end(), sort_by_abs);
    return v;
}

/*
 * Determines if word has only alphanum or single quote
 * characters
 */
bool valid_word(const string path) {
    return true;
    // iterate over characters, using c_str
}

/*
 * Returns a new lowercase string
 */
string to_lower(string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

/*
 * Splits a steam by delimiter
 */
vector<string> split_stream(std::istream& line_stream, const char& delim) {
    vector<string> tokens;
    string token;
    if (line_stream.good()) {
        while (std::getline(line_stream,token,delim)) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

/*
 * Splits a string by a delimiting character.
 */
vector<string> split(const string& line, const char& delim) {
    std::istringstream line_stream(line);
    return split_stream(line_stream, delim);
}

/*
 * Splits an input string into a matrix of tokens according to a
 * token delimiter and a line delimiter
 */
vector<vector<string>> split_lines_stream(std::istream& ifs, const char& delim, const char& linedelim) {
    string line;
    vector<vector<string>> lines;
    while (std::getline(ifs,line,linedelim)) {
        vector<string> tokens = split(line, delim);
        lines.push_back(tokens);
    }
    return lines;
}


/*!
 * Strips a string from its punctuation
 * @param s
 * @return
 */
string strip(string s) {
    if (s.size() == 0) {
        return "";
    }
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lalpha = to_lower(alpha);
    string num = "1234567890";

    string valid = alpha + lalpha + num + "'";
    auto start = s.find_first_of(valid);
    auto end   = s.find_last_of(valid);
    int len = end - start + 1;
    if (len <= 0) {
        std::cout << "Returning empty" << std::endl;
        return "";
    }
    return s.substr(start, end - start+1);
}

/*
 * Whether a character is valid
 */
bool is_valid_char(const char& c) {
    return std::isalnum(c) || c == '\'';
}

/*
 * Whether a word is valid
 */
bool is_valid_word(const string&s) {
    for (auto it = s.cbegin(); it != s.cend(); it++) {
        if (!is_valid_char(*it)) {
            return false;
        }
    }
    return true;
}

/*
 * Reads a matrix csv
 */
TypedMatrix<double> read_matrix_csv(const string path) {
    // open file
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    if (ifs.fail()) {
        throw std::ios_base::failure("File doesn't exist");
    }

    vector<vector<string>> cells = split_lines_stream(ifs, ',', '\n');

    ifs.close();

    // initialize the matrix
    int num_rows = cells.size();
    int num_cols = cells[0].size();
    TypedMatrix<double> m = TypedMatrix<double>(num_rows, num_cols);
    // check if shape is a square

    // set each cell
    string::size_type sz;     // alias of size_t
    for (int i = 0; i < num_rows; i++) {
        if (cells[i].size() != num_cols) {
            throw std::ios_base::failure("CSV file is not the correct shape");
        }
        for (int j = 0; j < num_cols; j++) {
            double x = std::stod (cells[i][j],&sz);
            m.set(i, j, x);
        }
    }
    return m;
}

/*
 * Write matrix to csv
 */
void write_matrix_csv(const TypedMatrix<double> &matrix, const string path) {
    std::ofstream outfile;
    outfile.open (path);
    int rows, cols;
    rows = matrix.rows();
    cols = matrix.cols();


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outfile << std::to_string(matrix.get(i, j));
            if (j < cols-1) {
                outfile << ",";
            }
        }
        if (i < rows-1) {
            outfile << "\n";
        }
    }
    outfile.close();
}

std::map<string, int> occurrence_map(const string path) {
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    vector<vector<string>> words = split_lines_stream(ifs, ' ', '\n');
    ifs.close();

    std::map<string, int> map;

    vector< vector<string> >::iterator row;
    vector<string>::iterator col;
    for (row = words.begin(); row != words.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            string w = strip(*col);
            if (is_valid_word(w)) {
                if (w != "") {
                    map[to_lower(w)] += 1;
                }
            }
        }
    }

    return map;
}