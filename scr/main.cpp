#include "../include/DynamicArray.h"

#include <clocale>
#include <cstdlib>
#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;


static bool g_failAlloc = false;

void* operator new(size_t n) {
    if (g_failAlloc) throw bad_alloc();
    if (void* p = malloc(n ? n : 1)) return p;
    throw bad_alloc();
}
void* operator new[](size_t n) { return operator new(n); }
void operator delete(void* p) noexcept { free(p); }
void operator delete[](void* p) noexcept { free(p); }
void operator delete(void* p, size_t) noexcept { free(p); }
void operator delete[](void* p, size_t) noexcept { free(p); }

// ---------------------------------------------------------------------------

void testOutOfRange() {
    cout << "\n===== std::out_of_range (индекс вне границ) =====\n";
    DynamicArray arr(3);
    arr.set(0, 1); arr.set(1, 2); arr.set(2, 3);
    cout << "arr = "; arr.print(); cout << "\n";

    try {
        arr.set(5, 10);
    } catch (const out_of_range& e) {
        cout << "Поймано out_of_range (set): " << e.what() << "\n";
    }
    try {
        arr.set(-1, 10);
    } catch (const out_of_range& e) {
        cout << "Поймано out_of_range (set): " << e.what() << "\n";
    }
    try {
        cout << arr.get(3) << "\n";
    } catch (const out_of_range& e) {
        cout << "Поймано out_of_range (get): " << e.what() << "\n";
    }
}

void testInvalidArgument() {
    cout << "\n===== std::invalid_argument (значение вне -100..100) =====\n";
    DynamicArray arr(3);

    try {
        arr.set(0, 101);
    } catch (const invalid_argument& e) {
        cout << "Поймано invalid_argument (set): " << e.what() << "\n";
    }
    try {
        arr.push_back(-101);
    } catch (const invalid_argument& e) {
        cout << "Поймано invalid_argument (push_back): " << e.what() << "\n";
    }
    try {
        DynamicArray bad(0);
    } catch (const invalid_argument& e) {
        cout << "Поймано invalid_argument (конструктор): " << e.what() << "\n";
    }

    cout << "Массив после ошибок не изменился: "; arr.print(); cout << "\n";
    cout << "Корректные значения проходят: ";
    arr.set(0, 100); arr.push_back(-100);
    arr.print(); cout << "\n";
}

void testBadAlloc() {
    cout << "\n===== std::bad_alloc (нет памяти) =====\n";

    try {
        g_failAlloc = true;                 // «память закончилась»
        DynamicArray arr(1000);
        g_failAlloc = false;
    } catch (const bad_alloc& e) {
        g_failAlloc = false;
        cout << "Поймано bad_alloc (конструктор): " << e.what() << "\n";
    }

    DynamicArray arr(3);
    arr.set(0, 1); arr.set(1, 2); arr.set(2, 3);
    try {
        g_failAlloc = true;
        arr.push_back(4);
        g_failAlloc = false;
    } catch (const bad_alloc& e) {
        g_failAlloc = false;
        cout << "Поймано bad_alloc (push_back): " << e.what() << "\n";
    }
    cout << "Старый массив цел: "; arr.print();
    cout << "  size=" << arr.getSize() << "\n";
}

void testWorkingCase() {
    cout << "\n===== Обычная работа (без исключений) =====\n";
    DynamicArray a(4), b(2);
    a.set(0, 10); a.set(1, 20); a.set(2, 30); a.set(3, 40);
    b.set(0, 1);  b.set(1, 2);
    a.add(b);
    cout << "a.add(b) = "; a.print(); cout << "\n";
    a.sub(b);
    cout << "a.sub(b) = "; a.print(); cout << "\n";

    DynamicArray c = a;
    c.set(0, 99);
    cout << "a = "; a.print(); cout << ", копия c = "; c.print(); cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "===== ЧАСТЬ 2. ИСКЛЮЧЕНИЯ =====\n";
    testOutOfRange();
    testInvalidArgument();
    testBadAlloc();
    testWorkingCase();
    cout << "\n===== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ =====\n";
    return 0;
}