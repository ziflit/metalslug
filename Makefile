# Para el cliente
SRC_FILES = src/*.cpp $(filter-out src/model/server.cpp, $(wildcard src/model/*.cpp)) src/Utils/*.cpp
INC_FILES = src/*.h -I$(filter-out src/model/server.h, $(wildcard src/model/*.h))
OBJ_NAME = client
CLIENT_DEP =

# Para el server
SRV_SRC_FILES = src/model/server.cpp
SRV_INC = src/model/server.h
SRV_DEP = -pthread
SRV_OBJ_NAME = server

# Para test
TEST_SRC_FILES = test/*.cpp
OBJ_NAME_TEST = metalslug_tests.out

# General
CC = g++
COMPILER_FLAGS = -w -std=c++11 -g -Wall
LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2main -lyaml-cpp -lSDL2_ttf


all : client server
#	$(CC) -I$(INC_FILES) $(SRC_FILES) $(COMPILER_FLAGS) -o $(OBJ_NAME)
#	$(CC) -I$(SRV_INC) $(SRV_SRC_FILES) $(SRV_DEP) $(COMPILER_FLAGS) -o $(SRV_OBJ_NAME)

client : $(SRC_FILES)
	$(CC) -I$(INC_FILES) $(SRC_FILES) $(COMPILER_FLAGS) -o $(OBJ_NAME)

server : $(SRV_SRC_FILES)
	$(CC) -I$(SRV_INC) $(SRV_SRC_FILES) $(SRV_DEP) $(COMPILER_FLAGS) -o $(SRV_OBJ_NAME)

test : $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(SRC_FILES) $(TEST_SRC_FILES) $(COMPILER_FLAGS) -lgtest -o $(OBJ_NAME_TEST)
