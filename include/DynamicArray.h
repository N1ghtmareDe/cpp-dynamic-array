#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

class DynamicArray {
private:
    int* data;
    int  size;

    static bool isValidValue(int value) {
        return value >= -100 && value <= 100;
    }

public:
    // Бросает std::invalid_argument (n <= 0), std::bad_alloc (нет памяти)
    explicit DynamicArray(int n);
    ~DynamicArray();

    // Бросает std::bad_alloc
    DynamicArray(const DynamicArray& other);

    void print() const;

    // Бросает std::out_of_range (индекс), std::invalid_argument (значение)
    void set(int index, int value);

    // Бросает std::out_of_range (индекс)
    int  get(int index) const;
    int  getSize() const { return size; }

    // Бросает std::invalid_argument (значение), std::bad_alloc (нет памяти)
    void push_back(int value);

    // Недостающие элементы считаются нулями, размер не меняется
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
};

#endif