CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC := src#Source directory
BIN := bin#Output directory


IN_FILES := $(filter-out main.cc test_gameobj.cc test_main.cc, $(notdir $(wildcard $(SRC)/*.cc)))

#Gives the files the correnct format
NECESSARY := $(addprefix $(SRC)/,$(IN_FILES))
BIN_NECESSARY := $(addprefix $(BIN)/,$(IN_FILES:.cc=.o))

all: game
leak: test clearscreen leak_run

game: $(BIN_NECESSARY) bin/main.o
	$(CCC) $(CFLAGS) $(BIN_NECESSARY) bin/main.o $(SFMLFLAGS) -o PlayingWithFire

test: $(BIN_NECESSARY) test_main.o test_gameobj.o
	$(CCC) $(CFLAGS)  $(BIN_NECESSARY) test_main.o test_gameobj.o -lsfml-graphics -lsfml-window -lsfml-system

#Created the compiled files.
bin/%.o: src/%.cc
	$(CCC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_NECESSARY) bin/main.o bin/test_gameobj.o PlayingWithFire

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./PlayingWithFire

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./PlayingWithFire


# -o  is a g++ flag for setting the name of the output file.
#
# -c  is a g++ flag that created binary files but does not link them together.
#
# $<  is a makefile placeholder for the input file name. That is the one that
#     the one that needs to be compiled.
#
# $@  is a makefile placeholder for the output file name. That is the one that
#     we want to make.
#
# OBS!!: The comments on lines 5-6 have to be directly after the directories.
