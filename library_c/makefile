CC = gcc
FLAGS = -Wall -Werror -Wextra
DEBUG = -g
VALDEB = valgrind
NAMEFILE = test_log.c sf_log.c
O = -o
NAME = test_logs
ARGV1 = Hello Name System 32
ARGV2 = Hello.

all: compile run run1 run2

deb: compile_deb run_deb run_deb1 run_deb2

clean: rm -rf $(NAME)


compile_deb:
	$(CC) $(FLAGS) $(DEBUG) $(NAMEFILE) $(O) $(NAME)

compile:
	$(CC) $(FLAGS) $(NAMEFILE) $(O) $(NAME)

run_deb:
	$(VALDEB) ./$(NAME)

run_deb1: 
	$(VALDEB) ./$(NAME) $(ARGV1)

run_deb2: 
	$(VALDEB) ./$(NAME) $(ARGV2)

run:
	./$(NAME)

run1:
	./$(NAME) $(ARGV1)

run2:
	./$(NAME) $(ARGV2)



