CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

NECESSARY = Powerup.cc State.cc Player.cc Bomb.cc PC.cc NPC.cc Menu_button.cc Fire.cc
BIN_NECESSARY := $(NECESSARY:.cc=.o)

all: test clearscreen run
leak: test clearscreen leak_run

main: $(BIN_NECESSARY) main.o
	$(CCC) $(CFLAGS) $(BIN_NECESSARY) main.o $(SFMLFLAGS)

test: $(BIN_NECESSARY) test_main.o test_gameobj.o fire_test.o player_test.o
	$(CCC) $(CFLAGS)  $(BIN_NECESSARY) test_main.o fire_test.o test_gameobj.o player_test.o -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cc
	$(CCC) $(CFLAGS) -c $<

clean:
	rm -r $(BIN_NECESSARY) main.o test_gameobj.o a.out a.out.dSYM/

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./a.out

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./a.out

