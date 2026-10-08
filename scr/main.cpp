#include "../include/DynamicArray.h"

#include <clocale>
#include <iostream>
#include <string>

using namespace std;

void testIntegral() {
    cout << "\n===== ЗАДАНИЕ 1: ЦЕЛОЧИСЛЕННЫЙ ТИП (int) =====\n";
    DynamicArray<int> arr(3);
    arr.set(0, 10); arr.set(1, -20); arr.set(2, 100);
    cout << "arr = " << arr << "\n";

    try {
        arr.set(0, 101);
    } catch (const invalid_argument& e) {
        cout << "invalid_argument (set 101): " << e.what() << "\n";
    }
    try {
        arr.push_back(-101);
    } catch (const invalid_argument& e) {
        cout << "invalid_argument (push_back -101): " << e.what() << "\n";
    }
    try {
        arr.set(3, 1);
    } catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << "\n";
    }

    arr.push_back(-100);
    cout << "После push_back(-100): " << arr << "  size=" << arr.getSize() << "\n";
}

void testDouble() {
    cout << "\n===== ЗАДАНИЕ 1: ДРУГОЙ ЧИСЛОВОЙ ТИП (double) =====\n";
    DynamicArray<double> d(2);
    d.set(0, 1000.5);     // для нецелых типов диапазон -100..100 НЕ проверяется
    d.set(1, -250.25);
    cout << "d = " << d << "  (значения вне -100..100 допустимы)\n";
}

void testString() {
    cout << "\n===== ЗАДАНИЕ 1: НЕЧИСЛОВОЙ ТИП (std::string) =====\n";
    DynamicArray<string> s(3);
    s.set(0, "привет");
    s.set(1, "мир");
    s.set(2, "C++");
    cout << "s = " << s << "\n";
    s.push_back("шаблоны");
    cout << "После push_back: " << s << "  size=" << s.getSize() << "\n";

    DynamicArray<string> copy = s;
    copy.set(0, "пока");
    cout << "s    = " << s << "\n";
    cout << "copy = " << copy << "\n";
}

void testOutputOperator() {
    cout << "\n===== ЗАДАНИЕ 2: ОПЕРАТОР << =====\n";
    DynamicArray<int> a(4);
    for (int i = 0; i < 4; ++i) a.set(i, i * 10);
    cout << "cout << a  ->  " << a << "\n";

    DynamicArray<string> s(2);
    s.set(0, "a"); s.set(1, "b");
    cout << "cout << s  ->  " << s << "\n";
}

void testDist() {
    cout << "\n===== ЗАДАНИЕ 3: РАССТОЯНИЕ МЕЖДУ МАССИВАМИ =====\n";

    cout << "\n--- Числовой тип (int) ---\n";
    DynamicArray<int> a(3), b(3);
    a.set(0, 1); a.set(1, 2); a.set(2, 3);
    b.set(0, 4); b.set(1, 6); b.set(2, 3);
    cout << "a = " << a << "\nb = " << b << "\n";
    cout << "dist(a, b) = " << a.dist(b) << "  (ожидается 5)\n";

    cout << "\n--- Числовой тип (double) ---\n";
    DynamicArray<double> x(2), y(2);
    x.set(0, 0.0); x.set(1, 0.0);
    y.set(0, 3.0); y.set(1, 4.0);
    cout << "dist(x, y) = " << x.dist(y) << "  (ожидается 5)\n";

    cout << "\n--- Разные размеры -> invalid_argument ---\n";
    DynamicArray<int> c(2);
    try {
        a.dist(c);
    } catch (const invalid_argument& e) {
        cout << "invalid_argument: " << e.what() << "\n";
    }

    cout << "\n--- Нечисловой тип (string) -> bad_typeid ---\n";
    DynamicArray<string> s1(2), s2(2);
    try {
        s1.dist(s2);
    } catch (const bad_typeid& e) {
        cout << "bad_typeid: " << e.what() << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "===== ЧАСТЬ 3. ШАБЛОНЫ =====\n";
    testIntegral();
    testDouble();
    testString();
    testOutputOperator();
    testDist();
    cout << "\n===== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ =====\n";
    return 0;
}
