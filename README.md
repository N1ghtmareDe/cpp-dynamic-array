Часть 3. Шаблоны
`DynamicArray<T>` — шаблонный класс (весь код в `include/DynamicArray.h`, `DynamicArray.cpp` больше не нужен).
Задание 1. Шаблон для любого `T`. Для целочисленных типов (`std::is_integral_v<T>`) в `set`/`push_back` проверяется диапазон `[-100, 100]` (`if constexpr`), для остальных — нет.
Задание 2. `operator<<` для вывода массива.
Задание 3. `dist(other)` — евклидово расстояние. Только для числовых типов (`std::is_arithmetic_v<T>`), иначе `std::bad_typeid`; разные размеры — `std::invalid_argument`.
В `main` показана работа с `int`, `double` (числовые) и `std::string` (нечисловой).
Сборка
```bash
make        # собрать
make run    # собрать и запустить
make clean  # очистить
```