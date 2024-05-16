#include <iostream>
#include <vector>
#include <unordered_map>

const int MAX_SIZE = 2 * 1000000000 + 1; // Максимальный размер доски
// Функция для проверки победы после каждого хода
int checkWinner(std::vector<std::pair<int, int>>& moves) {
    std::unordered_map<int, std::unordered_map<int, char>> board;
    int win_steps = 0;
    int code = 0;
    for (int i = 0; i < moves.size(); i++) {
        int row = moves[i].first;
        int col = moves[i].second;

        char symbol = (i % 2 == 0) ? 'X' : 'O'; // Определяем текущий символ для текущего игрока

        board[row][col] = symbol; // Помещаем символ игрока на доску

        // Проверяем победу только после того, как на доске есть минимальное количество символов для победы
        if (i >= 4) {
            // Проверяем победу по горизонталям, вертикалям и диагоналям
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    // Если мы не исследуем горизонтальную, вертикальную или диагональную линию
                    if (dr == 0 && dc == 0) continue;

                    int count = 0; // Счетчик символов текущего игрока в текущем направлении
                    for (int k = -4; k <= 4; k++) {
                        int r = row + k * dr;
                        int c = col + k * dc;
                        if (r >= 0 && r < MAX_SIZE && c >= 0 && c < MAX_SIZE && board[r][c] == symbol) {
                            count++;


                            if (count == 5) {
                                if (symbol == 'X') {
                                    code = 1;
                                } else {
                                    code = 2;
                                }
                                win_steps = i + 1;
                            }// Если нашли пять символов подряд - это победа
                        } else {
                            count = 0; // Если символ не подходит, сбрасываем счетчик
                        }
                    }
                }
            }
        }
        if (moves.size() > win_steps) {
            code = 3;

        }
    }

    return code; // Никто не победил после всех ходов
}



int main() {
    int n;
    std::cin >> n; // Число ходов

    std::vector<std::pair<int, int>> moves(n); // Список ходов

    for (int i = 0; i < n; i++) {
        int r, c;
        std::cin >> r >> c; // Читаем координаты хода
        moves[i] = std::make_pair(r, c); // Добавляем ход в список
    }

    int win_code = checkWinner(moves);

    if (win_code == 0) {
        std::cout << "Draw" << std::endl; // Если никто не победил, это ничья
    } else if (win_code == 3) {
        std::cout << "Inattention" << std::endl;
    } else {
        std::cout << ((win_code == 1) ? "First" : "Second") << std::endl; // Иначе выводим победителя
    }

    return 0;
}