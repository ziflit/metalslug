SRC_FILES = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
CLIENT_SRC= src/client.cpp
SERVER_SRC = src/server.cpp
TEST_SRC_FILES = test/*.cpp

CC = g++

COMPILER_FLAGS = -w -std=c++11 -g -Wall

LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2main -lyaml-cpp -lSDL2_ttf

OBJ_NAME = metalslug.out 
OBJ_NAME_TEST = metalslug_tests.out

all : $(SRC_FILES)
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) -o $(OBJ_NAME)

# make client
client : $(CLIENT_SRC)
	$(CC) $(CLIENT_SRC) $(COMPILER_FLAGS) -o client

#make server
server : $(SERVER_SRC)
	$(CC) $(SERVER_SRC) $(COMPILER_FLAGS) -o server

test : $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(SRC_FILES) $(TEST_SRC_FILES) $(COMPILER_FLAGS) -lgtest -o $(OBJ_NAME_TEST)
