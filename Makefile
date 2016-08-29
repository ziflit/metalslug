#SRC_FILES = $(filter-out src/main.cpp, $(wildcard src/Model*.cpp))
SRC_FILES = src/*.cpp $(filter-out src/model/server.cpp, $(wildcard src/model/*.cpp)) src/Utils/*.cpp
TEST_SRC_FILES = test/*.cpp

CC = g++

COMPILER_FLAGS = -w -std=c++11 -g -Wall

LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2main -lyaml-cpp -lSDL2_ttf

OBJ_NAME = metalslug.out 
OBJ_NAME_TEST = metalslug_tests.out

all : $(SRC_FILES)
	$(CC) -Isrc/*.h -I$(filter-out src/model/server.h, $(wildcard src/model/*.h)) $(SRC_FILES) $(COMPILER_FLAGS) -o $(OBJ_NAME) 

test : $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(SRC_FILES) $(TEST_SRC_FILES) $(COMPILER_FLAGS) -lgtest -o $(OBJ_NAME_TEST)
