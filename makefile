all:
	gcc tty-sorting.c -o tty-sorting -Wall -lm
run: all
	clear
	./tty-sorting
