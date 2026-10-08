#include "../include/DynamicArray.h"

using namespace std;

// Конструктор
DynamicArray::DynamicArray(int n) {
    if (n <= 0) {
        cerr << "Предупреждение: размер должен быть > 0. Установлен 1.\n";
        n = 1;
    }
    size = n;
    data = new int[size];
    for (int i = 0; i < size; ++i) data[i] = 0;
}

// Деструктор
DynamicArray::~DynamicArray() {
    delete[] data;
    data = nullptr;
    size = 0;
}

// Конструктор копирования (глубокое копирование)
DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
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
bool DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        cerr << "Ошибка set(): индекс " << index
             << " вне границ [0, " << size - 1 << "]\n";
        return false;
    }
    if (!isValidValue(value)) {
        cerr << "Ошибка set(): значение " << value
             << " вне диапазона [-100, 100]\n";
        return false;
    }
    data[index] = value;
    return true;
}

// Геттер с проверкой границ
int DynamicArray::get(int index) const {
    if (index < 0 || index >= size) {
        cerr << "Ошибка get(): индекс " << index
             << " вне границ [0, " << size - 1 << "]\n";
        return 0;
    }
    return data[index];
}

// push_back с расширением
bool DynamicArray::push_back(int value) {
    if (!isValidValue(value)) {
        cerr << "Ошибка push_back(): значение " << value
             << " вне диапазона [-100, 100]\n";
        return false;
    }
    int* newData = new int[size + 1];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    newData[size] = value;
    delete[] data;
    data = newData;
    size++;
    return true;
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