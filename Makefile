CCC = g++
CFLAGS = -std=c++17 

all: game clearscreen run
leak: game clearscreen leak_run


game: main.o
	$(CCC) $(CFLAGS) main.o -lsfml-graphics -lsfml-window -lsfml-system

g: 
	$(CCC) $(CFLAGS) Powerup.cc -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cc
	$(CCC) $(CFLAGS) -c $<

clean:
	rm -r a.out a.out.dSYM/

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./a.out

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./a.out
