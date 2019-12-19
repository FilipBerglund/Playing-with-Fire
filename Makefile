CCC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

SRC := src#Source directory
BIN := bin#Output directory

#All test related files need to have the name test in them
IN_TEST_FILES := $(notdir $(wildcard $(SRC)/*test*))

#Gives the files the correct format
SRC_TEST := $(addprefix $(SRC)/,$(IN_TEST_FILES))
BIN_TEST := $(addprefix $(BIN)/,$(IN_TEST_FILES:.cc=.o))

#The files that are necessary for the game
NECESSARY_IN_FILES := $(filter-out $(IN_TEST_FILES), $(notdir $(wildcard $(SRC)/*.cc)))

#Gives the files the correct format
SRC_NECESSARY := $(addprefix $(SRC)/,$(NECESSARY_IN_FILES))
BIN_NECESSARY := $(addprefix $(BIN)/,$(NECESSARY_IN_FILES:.cc=.o))

all: game

game: $(BIN_NECESSARY)
	$(CCC) $(CFLAGS) $(BIN_NECESSARY) -o PlayingWithFire $(SFMLFLAGS)

#Create the compiled binary files and put them in bin/
$(BIN)/%.o: $(SRC)/%.cc
	$(CCC) $(CFLAGS) -c $< -o $@

test: $(filter-out Main.cc, $(BIN_NECESSARY)) $(BIN_TEST)
	$(CCC) $(CFLAGS) $(filter-out $(BIN)/Main.o, $(BIN_NECESSARY)) $(BIN_TEST) $(SFMLFLAGS)

clean:
	rm -rf $(BIN_NECESSARY) $(BIN)/test_gameobj.o PlayingWithFire

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
# -c  is a g++ flag that creates binary files but does not link them together.
#
# $<  is a makefile placeholder for the input file name. That is the one that
#     the one that needs to be compiled.
#
# $@  is a makefile placeholder for the output file name. That is the one that
#     we want to make.
#
# OBS!!: The comments on lines 5-6 have to be directly after the directories.

