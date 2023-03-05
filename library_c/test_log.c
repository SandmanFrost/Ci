#include <locale.h>

#include "sf_log.h"

int main(int argc, char** argv) {
  LogStart(argv[0]);
  setlocale(LC_ALL, "rus");
  LogStatus(
      argv[0],
      "[RUS]: Проверка наличия аргументов.\n\t\t\t\t\t\t\t\t\t\tПодключение "
      "поддержки русского языка.");
  LogStatus(argv[0],
            "[ENG]: Checking for arguments.\n\t\t\t\t\t\t\t\t\t\tEnabling "
            "Russian language support.");
  if (argc == 1) LogStatus(argv[0], "[RUS]: Нет аргументов для обработки.");
  if (argc == 1)
    LogStatus(argv[0], "[ENG]: There are no arguments to process.");
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] = \"%s\"\n", i, argv[i]);
    LogStatus(argv[0], "[RUS]: Обработка аргумента:");
    LogStatus(argv[0], argv[i]);
    LogStatus(argv[0], "[ENG]: Argument Processing:");
    LogStatus(argv[0], argv[i]);
  }
  LogEnd(argv[0]);
}