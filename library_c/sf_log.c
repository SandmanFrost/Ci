#include "sf_log.h"

void LogInit(tim *t) {
    memset(t->stime, 0 , sizeof(t->stime));
}

void LogTime(tim *t) {
    struct tm *ti;
    const time_t timer = time(NULL);
    ti = localetime(&time);
    strftime(t->stime, sizeof(t->stime), "%Y-%m-%d %H:%M:%S", ti);
}

void LogPrint(FILE *f, tim *t, char *filename, char *text) {
    fprintf(f, "[LOG] [TIME %s]\t\t%s: %s\n", t->stime, filename, text);
}

void LogPrintNum(FILE *f, tim *t, char *filename, int num);
void LogPrintChar(FILE *f, tim *t, char *filename, char text);
void LogStart(char *filename);
void LogStatus(char *filename, char *status);
void LogStatusNumber(char *filename, int num);
void LogStatusChar(char *filename, char status);
void LogEnd(char *filename);