#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cmath>
#include <iostream>
#include <new>         // std::bad_alloc
#include <stdexcept>   // std::out_of_range, std::invalid_argument
#include <string>
#include <type_traits> // std::is_integral_v, std::is_arithmetic_v
#include <typeinfo>    // std::bad_typeid

// Шаблонный динамический массив элементов типа T.
// Весь код в заголовке: шаблоны нельзя выносить в отдельный .cpp.
template <typename T>
class DynamicArray {
private:
    T*  data;
    int size;

    // Допустимый диапазон -100..100 проверяется ТОЛЬКО для целочисленных типов.
    // Для остальных типов (double, std::string, ...) значение всегда допустимо.
    static bool isValidValue(const T& value) {
        if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
            if constexpr (std::is_signed_v<T>) {
                return value >= -100 && value <= 100;
            } else {
                return value <= 100;
            }
        } else {
            (void)value;
            return true;
        }
    }

public:
    // Бросает std::invalid_argument (n <= 0), std::bad_alloc (нет памяти)
    explicit DynamicArray(int n) : data(nullptr), size(0) {
        if (n <= 0) {
            throw std::invalid_argument("Конструктор: размер должен быть > 0, получено " +
                                        std::to_string(n));
        }
        data = new T[n]();      // () — нулевая инициализация чисел / пустые строки
        size = n;
    }

    ~DynamicArray() {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    // Конструктор копирования (глубокое копирование)
    DynamicArray(const DynamicArray& other) : data(nullptr), size(0) {
        data = new T[other.size];
        size = other.size;
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }

    int getSize() const { return size; }

    // Бросает std::out_of_range (индекс).
    // Для целочисленных T дополнительно бросает std::invalid_argument,
    // если значение вне [-100, 100].
    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("set(): индекс " + std::to_string(index) +
                                    " вне границ [0, " + std::to_string(size - 1) + "]");
        }
        if constexpr (std::is_integral_v<T>) {
            if (!isValidValue(value)) {
                throw std::invalid_argument("set(): значение вне диапазона [-100, 100]");
            }
        }
        data[index] = value;
    }

    // Бросает std::out_of_range (индекс)
    const T& get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("get(): индекс " + std::to_string(index) +
                                    " вне границ [0, " + std::to_string(size - 1) + "]");
        }
        return data[index];
    }

    // Добавление в конец с расширением. Для целочисленных T — проверка диапазона.
    void push_back(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (!isValidValue(value)) {
                throw std::invalid_argument("push_back(): значение вне диапазона [-100, 100]");
            }
        }
        T* newData = new T[size + 1];
        for (int i = 0; i < size; ++i) newData[i] = data[i];
        newData[size] = value;
        delete[] data;
        data = newData;
        ++size;
    }

    // Поэлементное сложение/вычитание. Недостающие элементы other считаются 0.
    // (Работают только для типов, у которых есть + и - соответственно.)
    void add(const DynamicArray& other) {
        for (int i = 0; i < size; ++i) {
            T b = (i < other.size) ? other.data[i] : T();
            data[i] = data[i] + b;
        }
    }

    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; ++i) {
            T b = (i < other.size) ? other.data[i] : T();
            data[i] = data[i] - b;
        }
    }

    // Задание 3: евклидово расстояние  sqrt( sum (a[i]-b[i])^2 ).
    // Только для числовых типов, иначе std::bad_typeid.
    // Размеры должны совпадать, иначе std::invalid_argument.
    double dist(const DynamicArray& other) const {
        if constexpr (!std::is_arithmetic_v<T>) {
            (void)other;
            throw std::bad_typeid();
        } else {
            if (size != other.size) {
                throw std::invalid_argument("dist(): размеры массивов не совпадают (" +
                                            std::to_string(size) + " и " +
                                            std::to_string(other.size) + ")");
            }
            double sum = 0.0;
            for (int i = 0; i < size; ++i) {
                double d = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
                sum += d * d;
            }
            return std::sqrt(sum);
        }
    }

    // Задание 2: оператор вывода <<
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "[ ";
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) os << ", ";
        }
        os << " ]";
        return os;
    }
};

#endif
