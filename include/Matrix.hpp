#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include "Vector.hpp"     // for check_finite (and Vector itself, needed from ex07 on)

// Matrix<K>: rows x cols, stored ROW-MAJOR in one flat array: {{1, 2}, {3, 4}} means rows [1 2] and [3 4].
// Element (i, j) lives at _data[i * _cols + j].
template <typename K>
class Matrix {
private:
    size_t         _rows;
    size_t         _cols;
    std::vector<K> _data;
    template <typename F>
    void apply(const Matrix<K>& m, F op, const char* msg){
        if (this->rows() != m.rows() || this->cols() != m.cols())
            throw std::invalid_argument(msg);
        for(size_t i = 0; i < this->rows(); i++){
            for(size_t j = 0; j < this->cols(); j++){
                K value = op(_data[i * _cols + j], m(i, j));
                check_finite(value);        // check before writing: an overflow never lands in the matrix
                _data[i * _cols + j] = value;
            }
        }
    }

public:
    Matrix() : _rows(0), _cols(0) {}
    Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
        // rows * cols can be too big for a size_t and wrap around to a small wrong number: refuse it.
        if (cols != 0 && rows > _data.max_size() / cols)
            throw std::length_error("Matrix: too big");
        _data.assign(rows * cols, K());
    }
    // Matrix<float> m = {{1, 2}, {3, 4}};  → rows [1 2] and [3 4]
    Matrix(std::initializer_list<std::initializer_list<K> > rows) : _rows(rows.size()), _cols(0) {
        if (_rows > 0)
            _cols = rows.begin()->size();
        for (const std::initializer_list<K>& row : rows) {
            if (row.size() != _cols)
                throw std::invalid_argument("Matrix: rows of different lengths");
            _data.insert(_data.end(), row.begin(), row.end());
        }
    }

    size_t   rows() const { return _rows; }
    size_t   cols() const { return _cols; }
    bool     is_square() const { return _rows == _cols; }
    // The largest size (absolute value) of any number; throws on inf/nan. Used by row_echelon, determinant, inverse.
    // Time O(rows * cols): each number once. Space O(1).
    K biggest_abs() const {
        K biggest = K();
        for (size_t i = 0; i < this->rows(); i++){
            for (size_t j = 0; j < this->cols(); j++){
                check_finite((*this)(i, j));
                if (ft_abs((*this)(i, j)) > biggest)
                    biggest = ft_abs((*this)(i, j));
            }
        }
        return biggest;
    }
    // Checks the row and column, instead of reading memory that isn't ours.
    K& operator()(size_t i, size_t j) {
        if (i >= _rows || j >= _cols)
            throw std::out_of_range("Matrix: index out of range");
        return _data[i * _cols + j];
    }
    const K& operator()(size_t i, size_t j) const {
        if (i >= _rows || j >= _cols)
            throw std::out_of_range("Matrix: index out of range");
        return _data[i * _cols + j];
    }
    // ex00 add / sub / scl. n = rows * cols numbers.
    // Time O(n): each number once. Space O(1) extra: writes into this matrix.
    void add (const Matrix<K>& m){
        apply(m, [](K a, K b){return a + b;}, "add: size mismatch");
    }
    void sub (const Matrix<K>& m){
        apply(m, [](K a, K b){return a - b;}, "sub: size mismatch");
    }
    void scl (K a){
        for(size_t i = 0; i < this->rows(); i++){
            for(size_t j = 0; j < this->cols(); j++){
                K value = _data[i * _cols + j] * a;
                check_finite(value);
                _data[i * _cols + j] = value;
            }
        }
    }
    
    // ex07. This matrix is m x n, u has n numbers.
    // Time O(nm): two nested loops, rows x columns multiply-adds. Space O(m): the result vector (subject allows O(nm)).
    Vector<K> mul_vec(const Vector<K>& u) const {
        if (this->cols() != u.size())
            throw std::invalid_argument("mul_vec: size mismatch");
        Vector<K> result(this->rows());
        for (size_t i = 0; i < this->rows(); i++){
            for(size_t j = 0; j < this->cols(); j++){
                result[i] = std::fma((*this)(i, j), u[j], result[i]); //formula is a * b + c, a=(*this)(i, j), b=u[j], c=result[i], can be written as result[i] += (*this)(i, j) * u[j];
                check_finite(result[i]);
            }
        }
        return result;
    }

    // ex07. (m x n) times (n x p).
    // Time O(nmp): three nested loops, m * p results, each a sum of n products. Space O(mp): the result (subject allows O(nm + mp + np)).
    Matrix<K> mul_mat(const Matrix<K>& b) const {
        if (this->cols() != b.rows())
            throw std::invalid_argument("mul_mat: size mismatch"); // rule is: (m x n) * (n x p) = (m x p), n must match
        Matrix<K> result(this->rows(), b.cols());
        for (size_t i = 0; i < this->rows(); i++){
            for (size_t j = 0; j < b.cols(); j++){
                for (size_t k = 0; k < this->cols(); k++){
                    result(i, j) = std::fma((*this)(i, k), b(k, j), result(i, j));
                    check_finite(result(i, j));
                }
            }
        }
        return result;
    }

    // ex08. Time O(n): only the n diagonal numbers are read. Space O(1).
    K trace() const {
        if (!this->is_square())
            throw std::invalid_argument("trace: not a square matrix");
        K result = K();
        for (size_t i = 0; i < this->rows(); i++){
            result += (*this)(i, i);
            check_finite(result);
        }
        return result;
    }

    // ex09. m x n in, n x m out. Time O(nm): one assignment per number. Space O(nm): the new matrix.
    Matrix<K> transpose() const{
        Matrix<K> result(this->cols(), this->rows());
        for (size_t i = 0; i < this->rows(); i++){
            for (size_t j = 0; j < this->cols(); j++){
                check_finite((*this)(i, j));
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    // ex10. n = the size of the matrix (largest of rows, cols).
    // Time O(n^3): columns x rows x numbers per row in the elimination; biggest_abs, shrink and cleanup are n^2 each,
    // next to it, not inside it: n^3 + 3n^2 <= 4n^3. Space O(n^2): the copy m.
    Matrix<K> row_echelon() const{
        Matrix<K> m = *this;
        size_t lead = 0; // the first pivot goes in row 0
        K biggest = biggest_abs();
        // shrink the copy so its biggest number is 1: then one fixed tol works for huge and tiny matrices
        if (biggest > 0){
            for (size_t i = 0; i < m.rows(); i++){
                for (size_t k = 0; k < m.cols(); k++){
                    m(i, k) = m(i, k) / biggest;
                }
            }
        }
        K tol = 1e-6; // anything smaller than this is considered 0
        for(size_t c = 0; c < m.cols() && lead < m.rows(); c++){
            size_t p = lead;
            for (size_t r = lead + 1; r < m.rows(); r++){
                if (ft_abs(m(r, c)) > ft_abs(m(p, c)))
                    p = r;
            }
            if(ft_abs(m(p, c)) <= tol)
                continue; // column is all zeros, go to next column
            if (p != lead){
                for (size_t k = 0; k < m.cols(); k++){
                    std::swap(m(lead, k), m(p, k));
                }
            }
            K pivot = m(lead, c);
            for (size_t k = 0; k < m.cols(); k++){
                m(lead, k) = m(lead, k) / pivot;
            }
            for (size_t r = 0; r < m.rows(); r++){
                if (r != lead){
                    K factor = m(r, c);
                    for (size_t k = 0; k < m.cols(); k++){
                        m(r, k) = m(r, k) - factor * m(lead, k);
                    }
                }
            }
            lead++;
        }
        for (size_t i = 0; i < m.rows(); i++){
            for (size_t j = 0; j < m.cols(); j++){
                if (ft_abs(m(i, j)) <= tol)
                    m(i, j) = 0;
                check_finite(m(i, j));
            }
        }
        return m;
    }

    // ex11. Time O(n^3): columns x rows below x numbers per row; the other loops are n^2: n^3 + 4n^2 <= 5n^3.
    // Space O(n^2): the copy m, plus a few variables that do not grow with n.
    K determinant() const{
        if (!this->is_square())
            throw std::invalid_argument("determinant: not a square matrix");
        Matrix<K> m = *this;
        K det = K(1);
        size_t lead = 0; // the first pivot goes in row 0
        K biggest = biggest_abs();
        K tol = biggest * 1e-6; // anything smaller than this is considered 0
        for(size_t c = 0; c < m.cols() && lead < m.rows(); c++){
            size_t p = lead;
            for (size_t r = lead + 1; r < m.rows(); r++){
                if (ft_abs(m(r, c)) > ft_abs(m(p, c)))
                    p = r;
            }
            if(ft_abs(m(p, c)) <= tol)
                return 0; // no pivot in this column: space is squashed flat, so det = 0
            if (p != lead){
                for (size_t k = 0; k < m.cols(); k++){
                    std::swap(m(lead, k), m(p, k));
                }
                det *= -1; // swapping rows changes the sign of the determinant
            }
            for (size_t r = lead + 1; r < m.rows(); r++){
                K factor = m(r, c) / m(c, c);
                for (size_t k = 0; k < m.cols(); k++){
                    m(r, k) = m(r, k) - factor * m(lead, k);
                }
            }
            det = det * m(c, c);
            lead++;
        }
        check_finite(det);
        return det;
    }

    // ex12. Time O(n^3): row_echelon on the n x 2n matrix costs n * n * 2n = 2n^3; building w and copying out are n^2.
    // Space O(n^2): w and r (2n^2 numbers each) and inv (n^2): 5n^2.
    Matrix<K> inverse() const{
        if (!this->is_square())
            throw std::invalid_argument("inverse: not a square matrix");
        size_t n = this->rows();
        if (n == 0)
            return Matrix<K>(); // empty matrix: moves nothing, so its inverse is itself (det of 0x0 is 1)
        K biggest = biggest_abs();
        if (biggest == K(0))
            throw std::invalid_argument("inverse: matrix is singular");
        Matrix<K> w(n, 2 * n);
        for (size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                w(i, j) = (*this)(i, j) / biggest; // shrink A so its biggest number is 1, the same size as the identity's 1s
            }
            w(i, n + i) = K(1);
        }
        Matrix<K> r = w.row_echelon();
        for (size_t i = 0; i < n; i++){
            if (r(i, i) != K(1))
                throw std::invalid_argument("inverse: matrix is singular");
        }
        Matrix<K> inv(n, n);
        for(size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                inv(i, j) = r(i, n + j) / biggest; // un-shrink the inverse
                check_finite(inv(i, j));
            }
        }
        return inv;
    }
    
    // ex13. Time O(n^3): row_echelon; counting the non-zero rows adds at most rows x cols = n^2, which is dropped.
    // Space O(n^2): the reduced copy r.
    size_t rank() const{
        Matrix<K> r = this->row_echelon();
        size_t count = 0;
        for (size_t i = 0; i < r.rows(); i++){
            bool non_zero_row = false;
            for (size_t j = 0; j < r.cols(); j++){
                if (r(i, j) != K(0)){
                    non_zero_row = true;
                    break;
                }
            }
            if (non_zero_row)
                count++;
        }
        return count;
    }
};

template <typename K>
Matrix<K> operator+(Matrix<K> a, const Matrix<K> &b) { a.add(b); return a; }

template <typename K>
Matrix<K> operator-(Matrix<K> a, const Matrix<K> &b) { a.sub(b); return a; }

template <typename K>
Matrix<K> operator*(Matrix<K> a, K t) { a.scl(t); return a; }

// Prints like the subject: one "[a, b, c]" per row.
template <typename K>
std::ostream& operator<<(std::ostream& os, const Matrix<K>& m) {
    for (size_t i = 0; i < m.rows(); ++i) {
        os << "[";
        for (size_t j = 0; j < m.cols(); ++j){
            K x = m(i, j);
            if (x == 0)
                x = 0;   // avoid printing -0
            os << x << (j + 1 < m.cols() ? ", " : "");
        }
        os << "]" << std::endl;
    }
    return os;
}

#endif
