#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class matrix {
private:
    double** data;
    int n_rows;
    int n_cols;
    
    void allocate(int rows, int cols);
    void deallocate();
    void copy_from(const matrix& other);
    
public:
    // Конструкторы
    matrix();
    matrix(int n, int m);
    matrix(double val);
    matrix(double* arr, int m);
    matrix(int n, double* arr);
    matrix(const char* str);
    matrix(const matrix& other);
    
    // Деструктор
    ~matrix();
    
    // Оператор присваивания
    matrix& operator=(const matrix& other);
    
    // Статические методы
    static matrix identity(int n);
    static matrix diagonal(double* vals, int n);
    
    // Методы доступа
    int rows() const;
    int columns() const;
    void set(int i, int j, double val);
    double get(int i, int j) const;
    
    // Пункты 11-12: возвращают новую матрицу
    matrix row(int i) const;    // строка как матрица 1×n
    matrix col(int j) const;    // столбец как матрица n×1
    
    // Оператор [] (1-й приоритет - строка)
    matrix operator[](int i) const;
    
    // Умножение на скаляр
    matrix operator*(double scalar) const;
    matrix& operator*=(double scalar);
    
    // Вывод
    friend std::ostream& operator<<(std::ostream& os, const matrix& m);
};

#endif
