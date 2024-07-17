#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Функция для вывода текущего состояния Вселенной
void printUniverse(const vector<vector<bool>>& universe, int generation, int liveCount) {
    cout << "Generation: " << generation << ", Live cells: " << liveCount << endl;
    for (const auto& row : universe) {
        for (bool cell : row) {
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
    return universe;
}

// Функция для подсчета живых соседей клетки
int countNeighbors(const vector<vector<bool>>& universe, int y, int x) {
    static const int offsets[] = {-1, 0, 1}; // Смещения для поиска соседей
    int count = 0;
    for (int dy : offsets) {
        for (int dx : offsets) {
            if (dy == 0 && dx == 0) continue; // Пропуск самой клетки
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < universe.size() && nx >= 0 && nx < universe[0].size()) {
                count += universe[ny][nx]; // Суммирование состояния соседей
            }
        }
    }
    return count;
}

// Функция для обновления состояния Вселенной
vector<vector<bool>> updateUniverse(const vector<vector<bool>>& current) {
    vector<vector<bool>> next = current; // Копирование текущего состояния для обновления
    for (int y = 0; y < current.size(); y++) {
        for (int x = 0; x < current[0].size(); x++) {
            int neighbors = countNeighbors(current, y, x); // Подсчет соседей для клетки
            bool live = (neighbors == 3 || (neighbors == 2 && current[y][x])); // Правила игры для определения состояния клетки
            next[y][x] = live; // Обновление состояния клетки
        }
    }
    return next; // Возвращение нового состояния
}

int main() {
    string filename = "/Users/admin/Desktop/txt.txt"; // Файл с начальным состоянием
    auto universe = readInitialSetup(filename); // Чтение начального состояния
    int generation = 0; // Номер поколения
    int liveCount;

    // Основной цикл игры
    while (true) {
        liveCount = 0; // Счетчик живых клеток
        for (const auto& row : universe) {
            for (bool cell : row) {
                liveCount += cell; // Подсчет живых клеток
            }
        }
        printUniverse(universe, generation, liveCount); // Вывод текущего состояния
        auto nextUniverse = updateUniverse(universe); // Обновление Вселенной
        if (nextUniverse == universe || liveCount == 0) { // Проверка условий завершения игры
            cout << "Game over at generation " << generation << " with " << liveCount << " live cells." << endl;
            break;
        }
        universe = nextUniverse;
        generation++;
    }

    return 0;
}


