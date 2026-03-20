#include "matrix.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

// Приватные методы
void matrix::allocate(int rows, int cols) {
    n_rows = rows;	//строки
    n_cols = cols;	//столбцы
    data = new double*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        data[i] = new double[n_cols]();
    }
}

void matrix::deallocate() {
    if (data) {
        for (int i = 0; i < n_rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
    n_rows = n_cols = 0;
}

void matrix::copy_from(const matrix& other) {
    allocate(other.n_rows, other.n_cols);
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Конструкторы
// 1) matrix( int n, int m ) – конструктор матрицы размера n´m со значениями 0.0
matrix::matrix() : data(nullptr), n_rows(0), n_cols(0) {}

matrix::matrix(int n, int m) {
    allocate(n, m);
}

// 2) матрица 1*1 с этим элементом;
matrix::matrix(double val) {
    allocate(1, 1);
    data[0][0] = val;
}

// 3) матрица-строка из массива длины m
matrix::matrix(double* arr, int m) {
    allocate(1, m);
    for (int j = 0; j < m; j++) {
        data[0][j] = arr[j];
    }
}

// 4) матрица-столбец из массива длины n;
matrix::matrix(int n, double* arr) {
    allocate(n, 1);
    for (int i = 0; i < n; i++) {
        data[i][0] = arr[i];
    }
}

// 5) читает из строкового представления
matrix::matrix(const char* str) {
    data = nullptr;
    n_rows = n_cols = 0;
    
    // Собираем все числа
    double numbers[1000];
    int num_count = 0;
    
    const char* p = str;
    while (*p) {
        // Пропускаем всё, кроме цифр, минуса и точки
        while (*p && !((*p >= '0' && *p <= '9') || *p == '-' || *p == '.')) {
            p++;
        }
        
        if (*p) {
            char* end;
            numbers[num_count] = strtod(p, &end);
            num_count++;
            p = end;
        }
    }
    
    if (num_count == 0) return;
    
    // Считаем количество строк по скобочкам
    int rows = 0;
    p = str;
    int brace_level = 0;
    while (*p) {
        if (*p == '{') {
            brace_level++;
            if (brace_level == 2) {  // начало строки матрицы
                rows++;
            }
        } else if (*p == '}') {
            brace_level--;
        }
        p++;
    }
    
    // Если не нашли строки (возможно формат без внешних скобок)
    if (rows == 0) {
        rows = 1;
    }
    
    int cols = num_count / rows;
    
    allocate(rows, cols);
    
    int idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = numbers[idx++];
        }
    }
}

//копирования
matrix::matrix(const matrix& other) {
    copy_from(other);
}

matrix::~matrix() {
    deallocate();
}

//присваивания
matrix& matrix::operator=(const matrix& other) {
    if (this != &other) {
        deallocate();
        copy_from(other);
    }
    return *this;
}

// 6) возвращает единичную матрицу размера n;
matrix matrix::identity(int n) {
    matrix m(n, n);
    for (int i = 0; i < n; i++) {
        m.data[i][i] = 1.0;
    }
    return m;
}

// 7) возвращает диагональную матрицу размера n с заданными элементами по главной диагонали;
matrix matrix::diagonal(double* vals, int n) {
    matrix m(n, n);
    for (int i = 0; i < n; i++) {
        m.data[i][i] = vals[i];
    }
    return m;
}

// 8-9) число стр, стб
int matrix::rows() const { return n_rows; }
int matrix::columns() const { return n_cols; }

// 10) присвоить значение элементу [i][j] 
void matrix::set(int i, int j, double val) {
    data[i][j] = val;
}
// получить значение элемента в позиции
double matrix::get(int i, int j) const {
    return data[i][j];
}

// 11) i-я строка в виде новой матрицы, если такая строка есть – 1-й приоритет
matrix matrix::row(int i) const {
    matrix result(1, n_cols);
    for (int j = 0; j < n_cols; j++) {
        result.data[0][j] = data[i][j];
    }
    return result;
}

// 12) j-й столбец в виде новой матрицы, если такой столбец есть – 2-й приоритет
matrix matrix::col(int j) const {
    matrix result(n_rows, 1);
    for (int i = 0; i < n_rows; i++) {
        result.data[i][0] = data[i][j];
    }
    return result;
}

// Оператор [] (1-й приоритет - строка)
matrix matrix::operator[](int i) const {
    return row(i);
}

// 13) Умножение на скаляр 1) создаем новую
matrix matrix::operator*(double scalar) const {
    matrix result(n_rows, n_cols);
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}
//                     2) меняем эту
matrix& matrix::operator*=(double scalar) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            data[i][j] *= scalar;
        }
    }
    return *this;
}

// 14) перегрузка операции << – вывод матрицы, в привычном двумерном виде.
std::ostream& operator<<(std::ostream& os, const matrix& m) {
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            os << m.get(i, j);
            if (j < m.columns() - 1) os << " ";
        }
        if (i < m.rows() - 1) os << "\n";
    }
    return os;
}
