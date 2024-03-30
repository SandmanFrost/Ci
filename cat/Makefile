all: s21_cat
	
s21_cat: s21_cat.o Flags.o
	gcc s21_cat.o Flags.o -o s21_cat

s21_cat.o: s21_cat.c s21_cat.h
	gcc -c -Wall -Werror -Wextra s21_cat.c

Flags.o: Flags.c s21_cat.h
	gcc -c -Wall -Werror -Wextra Flags.c

clean:
	rm -rf *.o
