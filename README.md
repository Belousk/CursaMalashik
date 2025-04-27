
# CursaMalashik

Это курсовой проект, состоящий из двух частей: графического приложения на Qt и консольной программы для работы с графами.

## Структура проекта

### 1. `cursaProga-master`

Графическое приложение на C++ с Qt:

- `CMakeLists.txt` — настройка сборки CMake.
- `customwidget.cpp`, `customwidget.h` — кастомный виджет.
- `mainwindow.cpp`, `mainwindow.h`, `mainwindow.ui` — главное окно и его интерфейс.
- `main.cpp` — запуск программы.

### 2. `cursaProga_part_2`

Консольная программа для работы с графами:

- `graph.txt` — файл с описанием графа.
- `dfs_result.txt` — результаты обхода графа в глубину (DFS).
- `main.cpp` — реализация считывания и обработки графа.

## Сборка и запуск

### 1. GUI-приложение (Qt)

Требуется:
- Qt 5.x или 6.x
- CMake 3.10+
- компилятор C++ (GCC, MSVC, Clang)

Сборка:
```bash
mkdir build
cd build
cmake ../cursaProga-master
cmake --build .
```

Запуск:
```bash
./cursaProga-master
```

### 2. Консольная программа (DFS)

Сборка и запуск:
```bash
cd cursaProga_part_2
g++ main.cpp -o graph_search
./graph_search
```

## Функциональность

- Часть 1: Визуализация/работа через GUI.
- Часть 2: Чтение графа из `graph.txt`, обход в глубину (DFS) с записью результатов в `dfs_result.txt`.

## Автор

[Ваше имя]  
Курсовой проект: графы и визуализация.
