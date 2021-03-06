CC = gcc
CFLAGS = -Wall -std=c99 -lm
LFLAGS = `pkg-config --libs --cflags sdl` -lSDL_ttf -lSDL_image -lSDL_mixer
LINKER = gcc -o
LFFLAGS_MAC =

SRCDIR = src
OBJDIR = obj
BINDIR = bin


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all : $(BINDIR)/Snake_Schlangà_SDL  $(BINDIR)/Snake_Schlangà_cmd $(BINDIR)/Tests_Snake

$(BINDIR)/Snake_Schlangà_SDL: $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@  $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Snake_Schlangà_SDL complete!"

$(BINDIR)/Snake_Schlangà_cmd: $(OBJDIR)/main_console.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@  $(OBJDIR)/main_console.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Snake_Schlangà_cmd complete!"

$(BINDIR)/Tests_Snake:  $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@ $(LFLAGS) $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Tests_Snake complete !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"
	

.PHONEY: mac
mac : $(BINDIR)/Snake_Schlangà_SDL_mac  $(BINDIR)/Snake_Schlangà_cmd_mac $(BINDIR)/Tests_Snake_mac

$(BINDIR)/Snake_Schlangà_SDL_mac: $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@  $(OBJDIR)/main.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Snake_Schlangà_SDL_mac complete!"

$(BINDIR)/Snake_Schlangà_cmd_mac: $(OBJDIR)/main_console.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@  $(OBJDIR)/main_console.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Snake_Schlangà_cmd_mac complete!"

$(BINDIR)/Tests_Snake_mac:  $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o
	@$(LINKER) $@ $(LFLAGS) $(OBJDIR)/Testmain.o $(OBJDIR)/affiche.o $(OBJDIR)/jeu.o $(OBJDIR)/snake.o $(OBJDIR)/collision.o $(OBJDIR)/strategie.o $(OBJDIR)/fruit.o $(LFLAGS)
	@echo "Linking for Tests_Snake_mac complete !"

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
