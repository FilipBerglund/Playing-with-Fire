CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC := src
BIN := bin

NECESSARY = Powerup.cc State.cc Player.cc Bomb.cc PC.cc NPC.cc Menu_button.cc Fire.cc NPC1.cc NPC2.cc NPC3.cc
BIN_NECESSARY := $(NECESSARY:.cc=.o)

DIR_NECESSARY := $(addprefix $(SRC)/, $(NECESSARY))
DIR_BIN_NECESSARY := $(addprefix $(BIN)/, $(BIN_NECESSARY))

all: game
leak: test clearscreen leak_run

game: $(DIR_BIN_NECESSARY) bin/main.o
	$(CCC) $(CFLAGS) $(DIR_BIN_NECESSARY) bin/main.o $(SFMLFLAGS) -o PlayingWithFire

test: $(BIN_NECESSARY) test_main.o test_gameobj.o
	$(CCC) $(CFLAGS)  $(BIN_NECESSARY) test_main.o test_gameobj.o -lsfml-graphics -lsfml-window -lsfml-system

bin/%.o: src/%.cc
	$(CCC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_BIN_NECESSARY) bin/main.o bin/test_gameobj.o PlayingWithFire

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./PlayingWithFire

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./PlayingWithFire

