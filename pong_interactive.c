#include <ncurses.h>  // Добавляем ncurses
#include <stdio.h>

#define gate_l 41
#define gate_r 40
#define center 124
#define careet 42
#define pole 61
#define ball 111

void drawPOLE(int ball_x, int ball_y, int careet_l, int careet_r, int gamer_r, int gamer_l);
void printDigitLine(int, int);
void printScoreboard(int, int);
int check_score(int);
int abs(int);

void drawPOLE(int ball_x, int ball_y, int careet_l, int careet_r, int gamer_r, int gamer_l) {
    clear();  // Очищаем экран перед отрисовкой нового кадра
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (j == 79) {
                printw("%c\n", gate_r);
            } else if (j == 0) {
                printw("%c", gate_l);
            } else if (i == 0 || i == 24) {
                printw("%c", pole);
            } else if (i == ball_y && j == ball_x) {
                printw("%c", ball);
            } else if (j == 39 || j == 41) {
                printw("%c", center);
            } else if ((j == 1 && abs(i - careet_l) <= 1) || (j == 78 && abs(i - careet_r) <= 1)) {
                printw("%c", careet);
            } else {
                printw(" ");
            }
        }
    }
    printScoreboard(gamer_l, gamer_r);
    refresh();  // Обновляем экран
}

void printDigitLine(int digit, int line) {
    if (digit == 0) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("| |");
        if (line == 2) printw("|_|");
    } else if (digit == 1) {
        if (line == 0) printw("   ");
        if (line == 1) printw("  |");
        if (line == 2) printw("  |");
    } else if (digit == 2) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw(" _|");
        if (line == 2) printw("|_ ");
    } else if (digit == 3) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw(" _|");
        if (line == 2) printw(" _|");
    } else if (digit == 4) {
        if (line == 0) printw("   ");
        if (line == 1) printw("|_|");
        if (line == 2) printw("  |");
    } else if (digit == 5) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("|_ ");
        if (line == 2) printw(" _|");
    } else if (digit == 6) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("|_ ");
        if (line == 2) printw("|_|");
    } else if (digit == 7) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("  |");
        if (line == 2) printw("  |");
    } else if (digit == 8) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("|_|");
        if (line == 2) printw("|_|");
    } else if (digit == 9) {
        if (line == 0) printw(" _ ");
        if (line == 1) printw("|_|");
        if (line == 2) printw(" _|");
    } else {
        printw("     ");
    }
}

void printScoreboard(int scoreL, int scoreR) {
    printw("\n");
    printw("  Player 1 %58s Player 2\n", "");
    printw("  ________ %58s ________\n", "");

    int digitL1 = scoreL / 10;
    int digitL2 = scoreL % 10;
    int digitR1 = scoreR / 10;
    int digitR2 = scoreR % 10;

    printw("%3s", "");
    printDigitLine(digitL1, 0);
    printDigitLine(digitL2, 0);
    printw("%62s", "");
    printDigitLine(digitR1, 0);
    printDigitLine(digitR2, 0);
    printw("\n");

    printw("%3s", "");
    printDigitLine(digitL1, 1);
    printDigitLine(digitL2, 1);
    printw("%62s", "");
    printDigitLine(digitR1, 1);
    printDigitLine(digitR2, 1);
    printw("\n");

    printw("%3s", "");
    printDigitLine(digitL1, 2);
    printDigitLine(digitL2, 2);
    printw("%62s", "");
    printDigitLine(digitR1, 2);
    printDigitLine(digitR2, 2);
    printw("\n");
}

int score_check(int ball_x, int ball_y, int careet_l, int careet_r, int gamer_r, int gamer_l) {
    if (gamer_l == 21 || gamer_r == 21) {
        drawPOLE(ball_x, ball_y, careet_l, careet_r, gamer_r, gamer_l);
        printw("\n%33sИгра завершена!\n\n", "");
        if (gamer_l == 21) {
            printw("%25sPlayer 1 победил со счетом %d - %d\n\n", "", gamer_l, gamer_r);
        } else {
            printw("%25sPlayer 2 победил со счетом %d - %d\n\n", "", gamer_r, gamer_l);
        }
        refresh();
        getch();  // Ожидание нажатия клавиши перед завершением
        return 1;
    }
    return 0;
}

int abs(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

int main(void) {
    initscr();              // Инициализация ncurses
    cbreak();               // Отключаем буферизацию ввода
    noecho();               // Отключаем автоматический вывод на экран
    keypad(stdscr, TRUE);   // Включаем обработку специальных клавиш
    nodelay(stdscr, TRUE);  // Неблокирующий ввод
    int ball_x = 40, ball_y = 12, direction_ball_x = 1, direction_ball_y = -1, gamer_l = 0, gamer_r = 0,
        careet_l = 11, careet_r = 11;
    while (1) {
        drawPOLE(ball_x, ball_y, careet_l, careet_r, gamer_r, gamer_l);
        int next_x = ball_x + direction_ball_x;
        int next_y = ball_y + direction_ball_y;
        if (next_x == 0) {
            ball_x = 40;
            ball_y = 12;
            gamer_r++;
            if (score_check(ball_x, ball_y, careet_l, careet_r, gamer_r, gamer_l)) break;
        } else if (next_x == 79) {
            ball_x = 40;
            ball_y = 12;
            gamer_l++;
            if (score_check(ball_x, ball_y, careet_l, careet_r, gamer_r, gamer_l)) break;
        } else {
            if ((next_x == 1 || next_x == 78) &&
                (abs(next_y - careet_l) <= 1 || abs(next_y - careet_r) <= 1)) {
                direction_ball_x *= -1;
            } else if (next_y == 0 || (next_y + 1) == 25) {
                direction_ball_y *= -1;
            }
            ball_x += direction_ball_x;
            ball_y += direction_ball_y;
        }
        int ch = getch();  // Получаем нажатую клавишу
        if (ch == 'q') {
            break;
        } else {
            if (ch == 'a' && careet_l > 1) {
                careet_l--;
            } else if (ch == 'z' && careet_l < 21) {
                careet_l++;
            } else if (ch == 'k' && careet_r > 1) {
                careet_r--;
            } else if (ch == 'm' && careet_r < 21) {
                careet_r++;
            }
        }
        napms(50);  // Задержка для управления скоростью игры
    }
    endwin();  // Завершение работы с ncurses
    return 0;
}