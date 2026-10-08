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
    explicit DynamicArray(int n);
    ~DynamicArray();

    DynamicArray(const DynamicArray& other);

    void print() const;
    bool set(int index, int value);
    int  get(int index) const;
    int  getSize() const { return size; }

    bool push_back(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
};

#endif