CC = gcc
CFLAGS = -Wall -std=c99 -lm

LINKER = gcc -o

SRCDIR = src
OBJDIR = obj
BINDIR = bin


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all : $(BINDIR)/Snake_Schlangà $(BINDIR)/Tests_Snake

$(BINDIR)/Snake_Schlangà: $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@ $(LFGLAGS)  $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o -lm
	@echo "Linking for Snake_Schlangà complete!"

$(BINDIR)/Tests_Snake:  $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@ $(LFLAGS) $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o -lm
	@echo "Linking for Tests_Snake complete !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"
	

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/*
	@echo "Executable removed!"

.PHONEY: dir
dir:
	mkdir bin obj
	@echo "Directories created !"
