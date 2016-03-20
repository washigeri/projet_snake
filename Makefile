# project name (generate executable with this name)
TARGET   = Snake_Schlangà

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -std=c99

LINKER   = gcc -o
# linking flags here
LFLAGS   = 

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin



all: bin/Snake_Schlangà bin/Snake_test

bin/Snake_Schlangà: obj/affiche.o obj/jeu.o obj/main.o obj/snake.o
	gcc obj/affiche.o obj/jeu.o obj/main.o obj/snake.o -o bin/Snake_Schlangà  $(CFLAGS)

bin/Snake_test: obj/affiche.o obj/jeu.o obj/maintest.o obj/snake.o
	gcc obj/affiche.o obj/jeu.o obj/main.o obj/snake.o -o bin/Snake_test $(CFLAGS)

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o $(CFLAGS)

obj/maintest.o: src/maintest.c
	gcc -c src/maintest.c -o obj/maintest.o $(CFLAGS)

obj/affiche.o: src/affiche.c
	gcc -c src/affiche.c -o obj/affiche.o $(CFLAGS)

obj/jeu.o: src/jeu.c
	gcc -c src/jeu.c -o obj/jeu.o $(CFLAGS)

obj/snake.o: src/snake.c
	gcc -c src/snake.c -o obj/snake.o $(CFLAGS)



