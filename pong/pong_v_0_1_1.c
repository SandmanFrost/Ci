// Version 0.1.1 Изменена игровая механика:
//                   Шар теперь отталкивается от угла каретки игрока.
//               Добавлено меню игры.
//               Добавлена пауза в игре.
//
//
// Version 0.1.0 Играбельная версия игры.
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 91
#define HEIGHT 25

typedef struct BallPoint {
  int x;
  int x_l;
  int y;
  int y_l;
  int nav;
  int x_nav;
  int y_nav;
} BallPoint;

typedef struct player {
  int p1;
  int p1_l;
  int p2;
  int p2_l;
} player;

typedef struct score {
  int s1;
  int s2;
} score_pl;

int menu();
void InitPlayerPosition(player *pl);
void InitBallPosition(BallPoint *ball);
void InitScore(score_pl *score);
void InitMap(char map[HEIGHT][WIDTH]);
void PrintMap(char map[HEIGHT][WIDTH]);
void AddInMapObj(char map[HEIGHT][WIDTH], player *pl, BallPoint *ball);
void PrintStatistic(score_pl *score);
void PlayerControl(int *key, player *pl);
void BallMove(BallPoint *ball, char map[HEIGHT][WIDTH]);
void Goal(BallPoint *ball, score_pl *score, player *pl,
          char map[HEIGHT][WIDTH]);
void RandStart(BallPoint *ball);

int main() {
  player pl;
  BallPoint ball;
  score_pl score;
  int q;
  int key;
  char map[HEIGHT][WIDTH];
  initscr();
  keypad(stdscr, TRUE);
  InitMap(map);
  while (q != 2) {
    halfdelay(1);
    q = menu();
    q++;
    InitPlayerPosition(&pl);
    InitBallPosition(&ball);
    InitScore(&score);
    while (q == 1) {
      noecho();
      curs_set(0);
      key = getch();
      PlayerControl(&key, &pl);
      BallMove(&ball, map);
      AddInMapObj(map, &pl, &ball);
      Goal(&ball, &score, &pl, map);
      PrintMap(map);
      PrintStatistic(&score);
      move(0, 0);
      curs_set(0);
      refresh();
      if (key == ' ') {
        halfdelay(10000);
        key = 1;
        while (key != ' ') {
          move(HEIGHT / 2, WIDTH / 2 - 3);
          printw("PAUSE");
          key = getch();
        }
        clear();
        halfdelay(1);
      }
      //   if (key == 'q') {
      //     clear();
      //     break;
      //   }
      if (score.s1 == 12) {
        clear();
        printw(
            "Player 1 WIN!\nSCORE: Pl 1: %d    Pl 2: %d\nPress ENTER to exit "
            "menu\n",
            score.s1, score.s2);
        halfdelay(100);
        do {
          noecho();
          curs_set(0);
          key = getch();
        } while (key != '\n');
        clear();
        move(0, 0);
        curs_set(0);
        break;
      }
      if (score.s2 == 12) {
        clear();
        printw(
            "Player 2 WIN!\nSCORE: Pl 1: %d    Pl 2: %d\nPress ENTER to exit "
            "menu\n",
            score.s1, score.s2);
        halfdelay(100);
        do {
          noecho();
          curs_set(0);
          key = getch();
        } while (key != '\n');
        clear();
        move(0, 0);
        curs_set(0);
        break;
      }
    }
  }
  endwin();
  return 0;
}

int menu() {
  int press;
  int q = 0;
  while (true) {
    noecho();
    curs_set(0);
    press = getch();
    if (press == KEY_UP) {
      if (q > 0) q--;
    }
    if (press == KEY_DOWN) {
      if (q < 1) q++;
    }
    if (q == 0)
      printw("-> New game\n");
    else
      printw("   New game\n");
    if (q == 1)
      printw("-> Exit\n");
    else
      printw("   Exit\n");
    if ((press == '\n') && (q == 0 || q == 1)) break;
    move(0, 0);
    curs_set(0);
    refresh();
  }
  curs_set(0);
  move(0, 0);
  refresh();
  clear();
  return q;
}

void InitPlayerPosition(player *pl) {
  pl->p1 = HEIGHT / 2;
  pl->p2 = HEIGHT / 2;
  pl->p1_l = pl->p1;
  pl->p2_l = pl->p2;
}

void InitBallPosition(BallPoint *ball) {
  ball->x = HEIGHT / 2;
  ball->y = WIDTH / 2;
  ball->x_l = ball->x;
  ball->y_l = ball->y;
  ball->nav = 0;
  ball->x_nav = 1;
  ball->y_nav = 1;
}

void InitScore(score_pl *score) {
  score->s1 = 0;
  score->s2 = 0;
}

void InitMap(char map[HEIGHT][WIDTH]) {
  for (int h = 0; h < HEIGHT; h++) {
    if (h != 0 && h != HEIGHT - 1) {
      for (int w = 0; w < WIDTH; w++) {
        if (w != 0 && w != WIDTH - 1)
          map[h][w] = ' ';
        else
          map[h][w] = '#';
      }
    } else
      for (int w = 0; w < WIDTH; w++) map[h][w] = '#';
  }
}

void PrintMap(char map[HEIGHT][WIDTH]) {
  for (int h = 0; h < HEIGHT; h++) {
    for (int w = 0; w < WIDTH; w++) {
      printw("%c", map[h][w]);
    }
    printw("\n");
  }
}

void AddInMapObj(char map[HEIGHT][WIDTH], player *pl, BallPoint *ball) {
  map[pl->p1_l][3] = ' ';
  map[pl->p1_l + 1][3] = ' ';
  map[pl->p1_l - 1][3] = ' ';
  map[pl->p2_l][87] = ' ';
  map[pl->p2_l + 1][87] = ' ';
  map[pl->p2_l - 1][87] = ' ';
  map[pl->p1][3] = 'I';
  map[pl->p1 + 1][3] = 'I';
  map[pl->p1 - 1][3] = 'I';
  map[pl->p2][87] = 'I';
  map[pl->p2 + 1][87] = 'I';
  map[pl->p2 - 1][87] = 'I';
  map[ball->x_l][ball->y_l] = ' ';
  map[ball->x][ball->y] = '*';
}

void PrintStatistic(score_pl *score) {
  if (score->s1 < 10 && score->s2 < 10)
    printw("\t\tPlayer 1:  %d \t\t\t\tPlayer 2:  %d\n", score->s1, score->s2);
  if (score->s1 < 10 && score->s2 > 9)
    printw("\t\tPlayer 1:  %d \t\t\t\tPlayer 2: %d\n", score->s1, score->s2);
  if (score->s1 > 9 && score->s2 < 10)
    printw("\t\tPlayer 1: %d \t\t\t\tPlayer 2:  %d\n", score->s1, score->s2);
  if (score->s1 > 9 && score->s2 > 9)
    printw("\t\tPlayer 1: %d \t\t\t\tPlayer 2: %d\n", score->s1, score->s2);
}

void PlayerControl(int *key, player *pl) {
  if (*key == KEY_UP) {
    if (pl->p2 - 1 != 1) {
      pl->p2_l = pl->p2;
      pl->p2 = pl->p2 - 1;
    }
  }
  if (*key == KEY_DOWN) {
    if (pl->p2 + 1 != (HEIGHT - 2)) {
      pl->p2_l = pl->p2;
      pl->p2 = pl->p2 + 1;
    }
  }
  if (*key == 'w') {
    if (pl->p1 - 1 != 1) {
      pl->p1_l = pl->p1;
      pl->p1 = pl->p1 - 1;
    }
  }
  if (*key == 's') {
    if (pl->p1 + 1 != (HEIGHT - 2)) {
      pl->p1_l = pl->p1;
      pl->p1 = pl->p1 + 1;
    }
  }
}

void BallMove(BallPoint *ball, char map[HEIGHT][WIDTH]) {
  ball->x_l = ball->x;
  ball->y_l = ball->y;
  if ((map[ball->x + ball->x_nav][ball->y + ball->y_nav] == 'I') &&
      (map[ball->x_l][ball->y + ball->y_nav] == ' ')) {
    ball->y_nav = ball->y_nav * -1;
    ball->x_nav = ball->x_nav * -1;
  }
  if (map[ball->x_l][ball->y + ball->y_nav] == 'I')
    ball->y_nav = ball->y_nav * -1;
  if (map[ball->x + ball->x_nav][ball->y + ball->y_nav] == 'I')
    ball->y_nav = ball->y_nav * -1;
  if ((ball->x + ball->x_nav) == 0 || (ball->x + ball->x_nav) == 24)
    ball->x_nav = ball->x_nav * -1;
  ball->x = ball->x_nav + ball->x;
  ball->y = ball->y_nav + ball->y;
}

void Goal(BallPoint *ball, score_pl *score, player *pl,
          char map[HEIGHT][WIDTH]) {
  if (ball->y == 1) {
    score->s2++;
    map[pl->p1][3] = ' ';
    map[pl->p1 + 1][3] = ' ';
    map[pl->p1 - 1][3] = ' ';
    map[pl->p2][87] = ' ';
    map[pl->p2 + 1][87] = ' ';
    map[pl->p2 - 1][87] = ' ';
    map[ball->x][ball->y] = ' ';
    ball->x = HEIGHT / 2;
    ball->y = WIDTH / 2;
    pl->p1 = HEIGHT / 2;
    pl->p2 = HEIGHT / 2;
    RandStart(ball);
  }
  if (ball->y == 89) {
    score->s1++;
    map[pl->p1][3] = ' ';
    map[pl->p1 + 1][3] = ' ';
    map[pl->p1 - 1][3] = ' ';
    map[pl->p2][87] = ' ';
    map[pl->p2 + 1][87] = ' ';
    map[pl->p2 - 1][87] = ' ';
    map[ball->x][ball->y] = ' ';
    ball->x = HEIGHT / 2;
    ball->y = WIDTH / 2;
    pl->p1 = HEIGHT / 2;
    pl->p2 = HEIGHT / 2;
    RandStart(ball);
  }
}

void RandStart(BallPoint *ball) {
  ball->nav = rand() % 4;
  if (ball->nav == 0) {
    ball->x_nav = 1;
    ball->y_nav = 1;
  }
  if (ball->nav == 1) {
    ball->x_nav = -1;
    ball->y_nav = 1;
  }
  if (ball->nav == 2) {
    ball->x_nav = -1;
    ball->y_nav = -1;
  }
  if (ball->nav == 3) {
    ball->x_nav = 1;
    ball->y_nav = -1;
  }
}