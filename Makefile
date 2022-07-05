build:
	gcc -std=c11 -g -O2 Stiva.c functions.c Coada.c main.c -o tema2
clear:	
	rm tema2
