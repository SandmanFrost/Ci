#include <stdio.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>

#define XMAX 18
#define YMAX 17

char GameScreenInit(char map[XMAX][YMAX]);
void GameScreeOnInput(char map[XMAX][YMAX]);
char BlockPillum(int x, int y, char map[XMAX][YMAX], int mapn[XMAX][YMAX]);
int NumBlockPillum(int x, int y, char map[XMAX][YMAX], int mapn[XMAX][YMAX]);


int main() {
    char map[XMAX][YMAX];
    int mapn[XMAX][YMAX];

    **map = GameScreenInit(map);
    GameScreeOnInput(map);
    return 0;
}

void GameScreeOnInput(char map[XMAX][YMAX]) {
     for (int i = 0; i < XMAX; i++) {
        for (int j = 0; j < YMAX; j++) {
            printf("%c", map[i][j]);
        }
    }
}
char GameScreenInit(char map[XMAX][YMAX]) {
    for (int i = 0; i < XMAX; i++) {
        for (int j = 0; j < YMAX; j++) {
            if ((i == 0) || (i == XMAX - 1)) {
                if (j == YMAX - 1) {
                    map[i][j] = '\n';
                } else {
                    map[i][j] = 'X';
                }
            } else {
                if ((j == 0) || (j == YMAX - 2)) {
                    map[i][j] = 'X';
                } else {
                    if (j == YMAX - 1) {
                        map[i][j] = '\n';
                    } else {
                        map[i][j] = ' ';
                    }
                }
            }
        }
    }
    return **map;
}
char BlockPillum(int x, int y, char map[XMAX][YMAX], int mapn[XMAX][YMAX]) {
    return **map;
}
int NumBlockPillum(int x, int y, char map[XMAX][YMAX], int mapn[XMAX][YMAX]) {
    return **mapn;
}

