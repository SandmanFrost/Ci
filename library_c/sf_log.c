#include "sf_log.h"

void LogInit(tim *t) { memset(t->stime, 0, sizeof(t->stime)); }

void LogTime(tim *t) {
  struct tm *ti;
  const time_t timer = time(NULL);
  ti = localetime(&time);
  strftime(t->stime, sizeof(t->stime), "%Y-%m-%d %H:%M:%S", ti);
}

void LogPrint(FILE *f, tim *t, char *filename, char *text) {
  fprintf(f, "[LOG] [TIME %s]\t\t%s: %s\n", t->stime, filename, text);
}

void LogPrintNum(FILE *f, tim *t, char *filename, int num) {
  fprintf(f, "[LOG] [TIME %s]\t\t%s: %d\n", t->stime, filename, num);
}

void LogPrintChar(FILE *f, tim *t, char *filename, char text) {
  fprintf(f, "[LOG] [TIME %s]\t\t%s: %c\n", t->stime, filename, text);
}

void LogStart(char *filename) {
  tim t;
  log_init(&t);
  FILE *f = fopen("LOG.txt", "w");
  log_time(&t);
  log_print(f, &t, filename, "BEGINING PROGRAMM");
  fclose(f);
  free(t.stime);
}

void LogStatus(char *filename, char *status) {
  tim t;
  log_init(&t);
  FILE *f = fopen("LOG.txt", "a+");
  log_time(&t);
  log_print(f, &t, filename, status);
  fclose(f);
  free(t.stime);
}

void LogStatusNumber(char *filename, int num) {
  tim t;
  log_init(&t);
  FILE *f = fopen("LOG.txt", "a+");
  log_time(&t);
  log_print_num(f, &t, filename, num);
  fclose(f);
  free(t.stime);
}

void LogStatusChar(char *filename, char status) {
  tim t;
  log_init(&t);
  FILE *f = fopen("LOG.txt", "a+");
  log_time(&t);
  log_print_char(f, &t, filename, status);
  fclose(f);
  free(t.stime);
}

void LogEnd(char *filename) {
  tim t;
  log_init(&t);
  FILE *f = fopen("LOG.txt", "a+");
  log_time(&t);
  log_print(f, &t, filename, "END PROGRAMM\n");
  fclose(f);
  free(t.stime);
}