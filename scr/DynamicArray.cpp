#include "../include/DynamicArray.h"

#include <new>        // std::bad_alloc
#include <stdexcept>  // std::out_of_range, std::invalid_argument
#include <string>

using namespace std;

// Конструктор
DynamicArray::DynamicArray(int n) : data(nullptr), size(0) {
    if (n <= 0) {
        throw invalid_argument("Конструктор: размер должен быть > 0, получено " + to_string(n));
    }
    data = new int[n];          // при нехватке памяти new сам бросит std::bad_alloc
    size = n;
    for (int i = 0; i < size; ++i) data[i] = 0;
}

// Деструктор
DynamicArray::~DynamicArray() {
    delete[] data;
    data = nullptr;
    size = 0;
}

// Конструктор копирования (глубокое копирование)
DynamicArray::DynamicArray(const DynamicArray& other) : data(nullptr), size(0) {
    data = new int[other.size]; // может бросить std::bad_alloc
    size = other.size;
    for (int i = 0; i < size; ++i) data[i] = other.data[i];
}

// Вывод
void DynamicArray::print() const {
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]";
}

// Сеттер с проверками
void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        throw out_of_range("set(): индекс " + to_string(index) +
                           " вне границ [0, " + to_string(size - 1) + "]");
    }
    if (!isValidValue(value)) {
        throw invalid_argument("set(): значение " + to_string(value) +
                               " вне диапазона [-100, 100]");
    }
    data[index] = value;
}

// Геттер с проверкой границ
int DynamicArray::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("get(): индекс " + to_string(index) +
                           " вне границ [0, " + to_string(size - 1) + "]");
    }
    return data[index];
}

// push_back с расширением
void DynamicArray::push_back(int value) {
    if (!isValidValue(value)) {
        throw invalid_argument("push_back(): значение " + to_string(value) +
                               " вне диапазона [-100, 100]");
    }
    // Сначала выделяем новую память: если new бросит bad_alloc,
    // старый массив останется целым и неизменным.
    int* newData = new int[size + 1];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    newData[size] = value;
    delete[] data;
    data = newData;
    ++size;
}

// add
void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size; ++i) {
        int b = (i < other.size) ? other.data[i] : 0;
        data[i] = data[i] + b;
    }
}

// sub
void DynamicArray::sub(const DynamicArray& other) {
    for (int i = 0; i < size; ++i) {
        int b = (i < other.size) ? other.data[i] : 0;
        data[i] = data[i] - b;
    }
}