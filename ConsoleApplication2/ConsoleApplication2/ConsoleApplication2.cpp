// Тестовое студента Абсалямов Данил Эдуардовича 3 курса университета на практику
// Резюме + портфолио: https://docs.google.com/document/d/1nZKKVr82Z71Srb6YzD3dg-lA1_EvKZEu37mPIaBYJls/edit?tab=t.0



#include <iostream>      
#include <fstream>       
#include <vector>        
#include <queue>         // Для очереди BFS
#include <string>        

using namespace std;

// Структура, представляющая точку на поле (строка и столбец)
struct Point {
    int row, col;
};

// Структура, представляющая направление движения
struct Direction {
    int dx, dy; // dx - горизонталь (вправо/влево), dy - вертикаль (вверх/вниз)
};

// Возможные направления движения: вверх, вниз, влево, вправо
const vector<Direction> directions = {
    {0, -1},  // вверх
    {0, 1},   // вниз
    {-1, 0},  // влево
    {1, 0}    // вправо
};

// Проверка, допустимо ли перейти в ячейку
bool is_valid(int r, int c, int rows, int cols, const vector<string>& maze, const vector<vector<bool>>& visited) {
    return r >= 0 && r < rows &&        // не выходит за границы по строкам
        c >= 0 && c < cols &&        // не выходит за границы по столбцам
        maze[r][c] != 'x' &&         // не стена
        !visited[r][c];              // не посещена
}

int main() {
    // 1. Чтение лабиринта из файла
    ifstream fin("input.txt");          // Открытие файла
    vector<string> maze;                // Сам лабиринт, построчно
    string line;
    while (getline(fin, line)) {        // Чтение каждой строки
        maze.push_back(line);
    }

    int rows = maze.size();             // Количество строк
    int cols = maze[0].size();          // Количество столбцов

    Point start = { -1, -1 }, finish = { -1, -1 }; // Координаты старта и финиша

    // 2. Поиск стартовой (S) и финишной (F) точек в лабиринте
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze[r][c] == 'S') {
                start = { r, c };
            }
            else if (maze[r][c] == 'F') {
                finish = { r, c };
            }
        }
    }

    // Проверка: найдены ли старт и финиш
    if (start.row == -1 || finish.row == -1) {
        cout << "Лабиринт должен содержать символы S и F\n";
        return 1;
    }

    // 3. Инициализация для BFS (поиск в ширину)
    queue<Point> q;                                          // Очередь для BFS
    vector<vector<bool>> visited(rows, vector<bool>(cols)); // Массив посещенных ячеек
    vector<vector<Point>> parent(rows, vector<Point>(cols)); // Родительская ячейка для восстановления пути

    visited[start.row][start.col] = true; // Помечаем старт как посещённый
    q.push(start);                        // Добавляем старт в очередь

    bool path_found = false;              // Флаг, найден ли путь

    // 4. BFS (поиск в ширину)
    while (!q.empty()) {
        Point current = q.front();        // Текущая ячейка
        q.pop();

        if (current.row == finish.row && current.col == finish.col) {
            path_found = true;           // Найден финиш
            break;
        }

        // Проверка всех 4 направлений
        for (const Direction& dir : directions) {
            int new_r = current.row + dir.dy;
            int new_c = current.col + dir.dx;

            // Если можно двигаться в новую ячейку
            if (is_valid(new_r, new_c, rows, cols, maze, visited)) {
                visited[new_r][new_c] = true;               // Отмечаем как посещённую
                parent[new_r][new_c] = current;             // Запоминаем, откуда пришли
                q.push({ new_r, new_c });                   // Добавляем новую точку в очередь
            }
        }
    }

    // 5. Восстановление пути, если найден
    if (path_found) {
        Point p = finish;
        while (!(p.row == start.row && p.col == start.col)) {
            if (maze[p.row][p.col] != 'F') {
                maze[p.row][p.col] = '*'; // Отметка пути символом '*'
            }
            p = parent[p.row][p.col];     // Двигаемся к родительской ячейке
        }
    }
    else {
        cout << "Путь не найден.\n";
        return 0;
    }

    // 6. Вывод лабиринта с отмеченным путём
    for (const string& row : maze) {
        cout << row << '\n';
    }
    int x;
    cin >> x;
    system("pause");
    return 0;


}
