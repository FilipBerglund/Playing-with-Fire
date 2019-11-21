CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors

NECESSARY = Powerup.cc State.cc Player.cc
BIN_NECESSARY := $(NECESSARY:.cc=.o)

all: test clearscreen run
leak: test clearscreen leak_run

test: $(BIN_NECESSARY) test_main.o test_gameobj.o
	$(CCC) $(CFLAGS)  $(BIN_NECESSARY) test_main.o test_gameobj.o -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cc
	$(CCC) $(CFLAGS) -c $<

clean:
	rm -r $(BIN_NECESSARY) test_gameobj.o a.out a.out.dSYM/

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./a.out

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./a.out
