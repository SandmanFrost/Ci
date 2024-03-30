#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc > 1)
    cat(argc, argv);
  else
    printf("cat: flags empty and file...\n");
  return 0;
}

void cat(int argc, char **argv) {
  FlagType flags;
  FlagsInit(&flags);
  int Error = 0;
  int i = 1;
  for (; i < argc; ++i) {
    if (strspn(argv[i], "-") == 0) break;
    if (Flags(argv[i], &flags) == 1) Error = 1;
  }
  if (flags.b == 1) flags.n = 0;
  if (!Error && i == argc) {
    printf("cat: please input filename...\n");
  }
  for (; !Error && i < argc; ++i) {
    FILE *f = fopen(argv[i], "r");
    if (f) {
      int LineStart = 1;
      int LineEmpety = 1;
      char Pred = '\n';
      char Next = ' ';
      char ch[1000] = {'\0'};
      while ((*ch = fgetc(f)) != EOF) {
        if ((flags.s == 1) && Flag_s(Pred, Next, *ch)) continue;
        if (flags.n == 1) LineStart = Flag_n(LineStart, &LineEmpety, *ch);
        if (flags.b == 1) Flag_b(Pred, &LineEmpety, *ch);
        if (flags.E == 1) Flag_E(*ch);
        if (flags.v == 1) Flag_v(ch);
        Next = Pred;
        Pred = *ch;
        if ((flags.T == 1) && Flag_T(*ch)) continue;
        if (*ch == '\0') {
          fputc(*ch, stdout);
        } else {
          fputs(ch, stdout);
        }
        memset(ch, '\0', 1000);
      }
      fclose(f);
    } else {
      printf("cat: Can't open '%s': No such file or directory!\n", argv[i]);
    }
  }
  if (Error)
    printf("cat: illegal option -- '%s'.\nTry 'man cat' for more information.\n",
           argv[i - 1]);
}