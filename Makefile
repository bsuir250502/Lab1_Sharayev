all:
	gcc -Wall -Wextra -pedantic -std=c99 1.c mylib.c -o lab1
clean:
	rm lab1
