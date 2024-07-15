#include <iostream>
#include <vector>
#include <cstdlib>  // для функций rand и srand
#include <ctime>    // для функции time
#include <unistd.h> // для функции usleep
#include <thread>
using namespace std;

int arrSTR{20}, arrSTL{20}; // Глобальные переменные, задающие размеры поля.
// Функция для вывода поля
void printMasiv (const vector <vector <int>> & masiv){
  for (int i {}; i < arrSTR; ++i){
    for (int j{}; j < arrSTL; ++j){
      cout << (masiv[i][j] ? "O" : "."); // Вывод символа 'O' для живых клеток, '.' для мертвых
    }
    cout << "\n"; // Переход на новую строку после каждой строки поля
  }
}
// Функция для подсчёта количества живых соседей для клетки
int countCordinat (vector <vector <int>> & masiv, int y, int x){
  int count{}; // Счётчик живых соседей
  for (int i{-1}; i <= 1; i++){
    for (int j{-1}; j <= 1; j++){
      if (i == 0 && j == 0) continue; // Пропускаем саму клетку
      int yi = (y + i + arrSTR) % arrSTR; // Обработка краёв поля (периодические граничные условия)
      int xj = (x + j + arrSTL) % arrSTL;
      count += masiv[yi][xj]; // Подсчёт живых соседей
    }
  }
  return count;
}
// Функция для обновления поля
void abdateMasiv (vector <vector <int>> & masiv){
    vector <vector<int>> newMasiv = masiv; // Создание копии текущего состояния поля
    for (int i{}; i < arrSTR; i++){
        for (int j{}; j < arrSTL; j++){
            int neighbors = countCordinat(masiv, i, j); // Подсчёт живых соседей для клетки

            // Правила игры "Жизнь"
            if (newMasiv[i][j] == 1){
                newMasiv[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            }
            else if (neighbors == 3) {
                newMasiv[i][j] = 1; // Клетка возрождается, если у неё ровно три живых соседа
            }
        }
    }
    masiv = newMasiv; // Обновление поля
}

int main() {
  vector <vector<int>> masiv(arrSTR, vector<int>(arrSTL)); // Инициализация поля
  // Начальное заполнение поля случайными значениями
  for (int i{}; i < arrSTR; i++){
    for (int j{}; j < arrSTL; j++){
     masiv[i][j] = rand() % 2;
    }
  }
  // Бесконечный цикл для отображения эволюции поля
  while (true){
    system("clear"); // Очистка консоли
    printMasiv(masiv); // Вывод поля
    abdateMasiv(masiv); // Обновление поля
    this_thread::sleep_for(chrono::milliseconds(200)); // Пауза между шагами
  }
  return 0;
}
