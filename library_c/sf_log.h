#ifndef _SF_LOG_H_
#define _SF_LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct sf_time {
  char stime[40];
} tim;

void LogInit(tim *t);
void LogTime(tim *t);
void LogPrint(FILE *f, tim *t, char *filename, char *text);
void LogPrintNum(FILE *f, tim *t, char *filename, int num);
void LogPrintChar(FILE *f, tim *t, char *filename, char text);
void LogStart(char *filename);
void LogStatus(char *filename, char *status);
void LogStatusNumber(char *filename, int num);
void LogStatusChar(char *filename, char status);
void LogEnd(char *filename);

#endif /*  _SF_LOG_H_  */