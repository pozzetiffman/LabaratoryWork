#include <iostream>
#include <vector>    // Подключение библиотеки для использования контейнера vector
#include <fstream>   // Подключение библиотеки для работы с файлами
#include <string>    // Подключение библиотеки для использования класса string

using namespace std;

// Функция для вывода текущего состояния Вселенной
void printUniverse(const vector<vector<bool>>& universe, int generation, int liveCount) {
    cout << "Generation: " << generation << ", Live cells: " << liveCount << endl; // Вывод номера поколения и количества живых клеток
    for (const auto& row : universe) { // Проход по каждой строке Вселенной
        for (bool cell : row) { // Проход по каждой клетке в строке
            cout << (cell ? '*' : '-') << ' '; // Вывод символов '*' для живых и '-' для мертвых клеток
        }
        cout << endl; // Новая строка после завершения каждой строки Вселенной
    }
}

// Функция для чтения начального состояния Вселенной из файла
vector<vector<bool>> readInitialSetup(const string& filename) {
    ifstream file(filename); // Открытие файла
    int rows, cols;
    file >> rows >> cols; // Чтение размеров поля
    vector<vector<bool>> universe(rows, vector<bool>(cols, false)); // Создание поля с мертвыми клетками
    int y, x;
    while (file >> y >> x) { // Чтение координат живых клеток
        universe[y][x] = true; // Установка клетки в состояние "живая"
    }
    return universe; // Возвращение начального состояния Вселенной
}

// Функция для подсчета живых соседей клетки
int countNeighbors(const vector<vector<bool>>& universe, int y, int x) {
    static const int offsets[] = {-1, 0, 1}; // Смещения для поиска соседей
    int count = 0; // Инициализация счетчика живых соседей
    for (int dy : offsets) { // Проход по смещениям для строк
        for (int dx : offsets) { // Проход по смещениям для столбцов
            if (dy == 0 && dx == 0) continue; // Пропуск самой клетки
            int ny = y + dy; // Новая координата по оси Y
            int nx = x + dx; // Новая координата по оси X
            if (ny >= 0 && ny < universe.size() && nx >= 0 && nx < universe[0].size()) { // Проверка, находится ли соседняя клетка в пределах поля
                count += universe[ny][nx]; // Суммирование состояния соседей
            }
        }
    }
    return count; // Возвращение количества живых соседей
}

// Функция для обновления состояния Вселенной
vector<vector<bool>> updateUniverse(const vector<vector<bool>>& current) {
    vector<vector<bool>> next = current; // Копирование текущего состояния для обновления
    for (int y = 0; y < current.size(); y++) { // Проход по строкам текущего состояния
        for (int x = 0; x < current[0].size(); x++) { // Проход по столбцам текущего состояния
            int neighbors = countNeighbors(current, y, x); // Подсчет соседей для клетки
            bool live = (neighbors == 3 || (neighbors == 2 && current[y][x])); // Правила игры для определения состояния клетки
            next[y][x] = live; // Обновление состояния клетки
        }
    }
    return next; // Возвращение нового состояния
}

int main() {
    string filename = "/Users/admin/Desktop/txt.txt"; // Имя файла с начальным состоянием
    auto universe = readInitialSetup(filename); // Чтение начального состояния
    int generation = 0; // Инициализация номера поколения
    int liveCount; // Инициализация счетчика живых клеток

    // Основной цикл игры
    while (true) {
        liveCount = 0; // Сброс счетчика живых клеток
        for (const auto& row : universe) { // Проход по каждой строке Вселенной
            for (bool cell : row) { // Проход по каждой клетке в строке
                liveCount += cell; // Подсчет живых клеток
            }
        }
        printUniverse(universe, generation, liveCount); // Вывод текущего состояния
        auto nextUniverse = updateUniverse(universe); // Обновление Вселенной
        if (nextUniverse == universe || liveCount == 0) { // Проверка условий завершения игры
            cout << "Game over at generation " << generation << " with " << liveCount << " live cells." << endl; // Сообщение о завершении игры
            break; // Выход из цикла
        }
        universe = nextUniverse; // Обновление состояния Вселенной
        generation++; // Увеличение номера поколения
    }

    return 0;
}
