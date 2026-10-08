#include "../include/DynamicArray.h"
#include <iostream>

using namespace std;

void testTask1() {
    cout << "\n===== ЗАДАНИЕ 1: БАЗОВЫЙ КЛАСС =====\n";
    DynamicArray arr(5);
    cout << "Создан массив: "; arr.print(); cout << "\n";

    arr.set(0, 10); arr.set(1, -20); arr.set(2, 100);
    arr.set(3, -100); arr.set(4, 42);
    cout << "После set(): "; arr.print(); cout << "\n";

    cout << "\nПроверка ошибок set():\n";
    arr.set(-1, 5);
    arr.set(5, 5);
    arr.set(0, 101);
    arr.set(1, -101);

    cout << "\nЧтение через get():\n";
    for (int i = 0; i < arr.getSize(); ++i)
        cout << "  arr[" << i << "] = " << arr.get(i) << "\n";

    cout << "\nПроверка ошибок get():\n";
    cout << "  arr.get(-1) = " << arr.get(-1) << "\n";
    cout << "  arr.get(99) = " << arr.get(99) << "\n";
}

void testTask2() {
    cout << "\n===== ЗАДАНИЕ 2: КОНСТРУКТОР КОПИРОВАНИЯ =====\n";
    DynamicArray a(4);
    a.set(0, 1); a.set(1, 2); a.set(2, 3); a.set(3, 4);
    cout << "a = "; a.print(); cout << "\n";

    DynamicArray b = a;
    cout << "b = "; b.print(); cout << " (копия a)\n";

    b.set(0, 99);
    cout << "После b.set(0, 99):\n";
    cout << "  a = "; a.print(); cout << " (не изменился)\n";
    cout << "  b = "; b.print(); cout << " (изменился)\n";
}

void testTask3() {
    cout << "\n===== ЗАДАНИЕ 3: PUSH_BACK =====\n";
    DynamicArray arr(3);
    arr.set(0, 1); arr.set(1, 2); arr.set(2, 3);
    cout << "Исходный: "; arr.print(); cout << "\n";

    arr.push_back(40);
    cout << "push_back(40): "; arr.print();
    cout << "  size=" << arr.getSize() << "\n";

    arr.push_back(-100);
    cout << "push_back(-100): "; arr.print();
    cout << "  size=" << arr.getSize() << "\n";

    cout << "\nПроверка ошибок push_back():\n";
    arr.push_back(101);
    arr.push_back(-101);
    cout << "После: "; arr.print();
    cout << "  size=" << arr.getSize() << " (не изменился)\n";
}

void testTask4() {
    cout << "\n===== ЗАДАНИЕ 4: ADD / SUB =====\n";

    cout << "\n--- Одинаковые размеры ---\n";
    DynamicArray a(4), b(4);
    a.set(0, 10); a.set(1, 20); a.set(2, 30); a.set(3, 40);
    b.set(0, 1);  b.set(1, 2);  b.set(2, 3);  b.set(3, 4);
    cout << "a = "; a.print(); cout << "\n";
    cout << "b = "; b.print(); cout << "\n";
    a.add(b);
    cout << "a.add(b) → a = "; a.print(); cout << "\n";

    cout << "\n--- a больше b ---\n";
    DynamicArray c(5), d(3);
    c.set(0, 10); c.set(1, 20); c.set(2, 30); c.set(3, 40); c.set(4, 50);
    d.set(0, 1);  d.set(1, 2);  d.set(2, 3);
    cout << "c = "; c.print(); cout << "\n";
    cout << "d = "; d.print(); cout << "\n";
    c.add(d);
    cout << "c.add(d) → c = "; c.print(); cout << "\n";

    cout << "\n--- a меньше b ---\n";
    DynamicArray e(3), f(5);
    e.set(0, 10); e.set(1, 20); e.set(2, 30);
    f.set(0, 1);  f.set(1, 2);  f.set(2, 3);  f.set(3, 4);  f.set(4, 5);
    cout << "e = "; e.print(); cout << "\n";
    cout << "f = "; f.print(); cout << "\n";
    e.add(f);
    cout << "e.add(f) → e = "; e.print(); cout << "\n";

    cout << "\n--- Вычитание ---\n";
    DynamicArray g(4), h(4);
    g.set(0, 50); g.set(1, 40); g.set(2, 30); g.set(3, 20);
    h.set(0, 5);  h.set(1, 10); h.set(2, 15); h.set(3, 20);
    cout << "g = "; g.print(); cout << "\n";
    cout << "h = "; h.print(); cout << "\n";
    g.sub(h);
    cout << "g.sub(h) → g = "; g.print(); cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "===== ЧАСТЬ 1. DYNAMICARRAY =====\n";
    testTask1();
    testTask2();
    testTask3();
    testTask4();
    cout << "\n===== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ =====\n";
    return 0;
}