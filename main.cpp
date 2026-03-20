#include "matrix.h"
#include <iostream>
#include <sstream>

using namespace std;

void test_constructors() {
    cerr << "Test 1: Конструкторы\n";
    
    // matrix()
    matrix m1;
    if (m1.rows() != 0 || m1.columns() != 0) {
        cerr << "  FAILED: " << "конструктор по умолчанию дает неверный размер" << "\n";
        exit(1);
    }
    
    // matrix(int, int)
    matrix m2(2, 3);
    if (m2.rows() != 2 || m2.columns() != 3) {
        cerr << "  FAILED: " << "matrix(int,int) неверный размер" << "\n";
        exit(1);
    }
    
    // matrix(double)
    matrix m3(5.5);
    if (m3.rows() != 1 || m3.columns() != 1) {
        cerr << "  FAILED: " << "matrix(double) неверный размер" << "\n";
        exit(1);
    }
    if (m3.get(0, 0) != 5.5) {
        cerr << "  FAILED: " << "matrix(double) неверное значение" << "\n";
        exit(1);
    }
    
    // matrix(double*, int)
    double arr[] = {1.0, 2.0, 3.0};
    matrix m4(arr, 3);
    if (m4.rows() != 1 || m4.columns() != 3) {
        cerr << "  FAILED: " << "matrix(double*,int) неверный размер" << "\n";
        exit(1);
    }
    if (m4.get(0, 0) != 1.0 || m4.get(0, 2) != 3.0) {
        cerr << "  FAILED: " << "matrix(double*,int) неверные значения" << "\n";
        exit(1);
    }
    
    // matrix(int, double*)
    matrix m5(3, arr);
    if (m5.rows() != 3 || m5.columns() != 1) {
        cerr << "  FAILED: " << "matrix(int,double*) неверный размер" << "\n";
        exit(1);
    }
    if (m5.get(0, 0) != 1.0 || m5.get(2, 0) != 3.0) {
        cerr << "  FAILED: " << "matrix(int,double*) неверные значения" << "\n";
        exit(1);
    }
    
    // matrix(char*)
    matrix m6("{{1, 0, 0}, {0, 1, 0.5}}");
    if (m6.rows() != 2 || m6.columns() != 3) {
        cerr << "  FAILED: " << "matrix(char*) неверный размер" << "\n";
        exit(1);
    }
    if (m6.get(0, 0) != 1.0 || m6.get(0, 2) != 0.0) {
        cerr << "  FAILED: " << "matrix(char*) неверное значение в [0][2]" << "\n";
        exit(1);
    }
    if (m6.get(1, 0) != 0.0 || m6.get(1, 2) != 0.5) {
        cerr << "  FAILED: " << "matrix(char*) неверное значение в [1][2]" << "\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

void test_static_methods() {
    cerr << "Test 2: Статические методы (возвращаем единичную и диаг.матрицу с зад.элем.)\n";
    
    // identity
    matrix I = matrix::identity(3);
    if (I.rows() != 3 || I.columns() != 3) {
        cerr << "  FAILED: " << "identity() неверный размер" << "\n";
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                if (I.get(i, j) != 1.0) {
                    cerr << "  FAILED: " << "identity() диагональ не 1 в [" << i << "][" << j << "]" << "\n";
                    exit(1);
                }
            } else {
                if (I.get(i, j) != 0.0) {
                    cerr << "  FAILED: " << "identity() недиагональ не 0 в [" << i << "][" << j << "]" << "\n";
                    exit(1);
                }
            }
        }
    }
    
    // diagonal
    double diag[] = {1.5, 2.5, 3.5};
    matrix D = matrix::diagonal(diag, 3);
    if (D.rows() != 3 || D.columns() != 3) {
        cerr << "  FAILED: " << "diagonal() неверный размер" << "\n";
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                if (D.get(i, j) != diag[i]) {
                    cerr << "  FAILED: " << "diagonal() неверное значение на диагонали в [" << i << "][" << j << "]" << "\n";
                    exit(1);
                }
            } else {
                if (D.get(i, j) != 0.0) {
                    cerr << "  FAILED: " << "diagonal() недиагональ не 0 в [" << i << "][" << j << "]" << "\n";
                    exit(1);
                }
            }
        }
    }
    
    cerr << "  OK\n";
}

void test_row_col() {
    cerr << "Test 3: row() и col() методы\n";
    
    matrix m(2, 3);
    m.set(0, 0, 1.0); m.set(0, 1, 2.0); m.set(0, 2, 3.0);
    m.set(1, 0, 4.0); m.set(1, 1, 5.0); m.set(1, 2, 6.0);
    
    // Проверка row()
    matrix r = m.row(0); // первая строчка, ожидаем новую матрицу [1, 2, 3]
    if (r.rows() != 1 || r.columns() != 3) {
        cerr << "  FAILED: " << "row() неверный размер" << "\n";
        exit(1);
    }
    if (r.get(0, 0) != 1.0 || r.get(0, 1) != 2.0 || r.get(0, 2) != 3.0) {
        cerr << "  FAILED: " << "row() неверные значения" << "\n";
        exit(1);
    }
    
    // Проверка col()
    matrix c = m.col(1);
    if (c.rows() != 2 || c.columns() != 1) {
        cerr << "  FAILED: " << "col() неверный размер" << "\n";
        exit(1);
    }
    if (c.get(0, 0) != 2.0 || c.get(1, 0) != 5.0) {
        cerr << "  FAILED: " << "col() неверные значения" << "\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

void test_operator_bracket() {
    cerr << "Test 4: operator[] (возвращаем строку как матрицу)\n";
    
    matrix m(2, 3);
    m.set(0, 0, 1.0); m.set(0, 1, 2.0); m.set(0, 2, 3.0);
    m.set(1, 0, 4.0); m.set(1, 1, 5.0); m.set(1, 2, 6.0);
    
    // M[i] возвращает строку как матрицу
    matrix r = m[0];
    if (r.rows() != 1 || r.columns() != 3) {
        cerr << "  FAILED: " << "operator[] неверный размер" << "\n";
        exit(1);
    }
    if (r.get(0, 0) != 1.0 || r.get(0, 1) != 2.0 || r.get(0, 2) != 3.0) {
        cerr << "  FAILED: " << "operator[] неверные значения" << "\n";
        exit(1);
    }
    
    // Для доступа к элементу M[i][j] используем row().col()
    matrix elem = m[1].col(2);
    if (elem.rows() != 1 || elem.columns() != 1) {
        cerr << "  FAILED: " << "доступ к элементу M[i][j] неверный размер" << "\n";
        exit(1);
    }
    if (elem.get(0, 0) != 6.0) {
        cerr << "  FAILED: " << "доступ к элементу M[i][j] неверное значение" << "\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

void test_scalar_mul() {
    cerr << "Test 5: Умножение на скаляр\n";
    
    matrix m(2, 2);
    m.set(0, 0, 1.0); m.set(0, 1, 2.0);
    m.set(1, 0, 3.0); m.set(1, 1, 4.0);
    
    matrix r = m * 2.0;
    if (r.get(0, 0) != 2.0 || r.get(0, 1) != 4.0 ||
        r.get(1, 0) != 6.0 || r.get(1, 1) != 8.0) {
        cerr << "  FAILED: " << "operator* неверные значения" << "\n";
        exit(1);
    }
    
    m *= 2.0;
    if (m.get(0, 0) != 2.0 || m.get(1, 1) != 8.0) {
        cerr << "  FAILED: " << "operator*= неверные значения" << "\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

void test_copy() {
    cerr << "Test 6: Конструктор копирования и присваивания\n";
    
    matrix m1(2, 2);
    m1.set(0, 0, 1.0);
    
    // Конструктор копирования
    matrix m2 = m1;
    if (m2.rows() != 2 || m2.columns() != 2) {
        cerr << "  FAILED: " << "конструктор копирования неверный размер" << "\n";
        exit(1);
    }
    if (m2.get(0, 0) != 1.0) {
        cerr << "  FAILED: " << "конструктор копирования неверное значение" << "\n";
        exit(1);
    }
    
    // Оператор присваивания
    matrix m3;
    m3 = m1;
    if (m3.get(0, 0) != 1.0) {
        cerr << "  FAILED: " << "оператор присваивания неверное значение" << "\n";
        exit(1);
    }
    
    // Проверка независимости
    m1.set(0, 0, 5.0);
    if (m2.get(0, 0) != 1.0) {
        cerr << "  FAILED: " << "копия не независима (конструктор копирования)" << "\n";
        exit(1);
    }
    if (m3.get(0, 0) != 1.0) {
        cerr << "  FAILED: " << "копия не независима (оператор присваивания)" << "\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

void test_output() {
    cerr << "Test 7: Оператор вывода\n";
    
    matrix m(2, 3);
    m.set(0, 0, 1.0); m.set(0, 1, 2.0); m.set(0, 2, 3.0);
    m.set(1, 0, 4.0); m.set(1, 1, 5.0); m.set(1, 2, 6.0);
    
    stringstream ss;
    ss << m;
    string expected = "1 2 3\n4 5 6";
    if (ss.str() != expected) {
        cerr << "  FAILED: " << "operator<< выводит неверный формат" << "\n";
        cerr << "  Expected: \"" << expected << "\"\n";
        cerr << "  Got:      \"" << ss.str() << "\"\n";
        exit(1);
    }
    
    cerr << "  OK\n";
}

int main() {
    cerr << "Matrix class тесты (вариант 4.1 (3 звезды))\n";
    cerr << "================================\n\n";
    
    test_constructors();
    test_static_methods();
    test_row_col();
    test_operator_bracket();
    test_scalar_mul();
    test_copy();
    test_output();
    
    cerr << "\nВсе тесты отработали успешно!\n";
    return 0;
}
