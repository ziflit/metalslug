#OBJS = src/*.cpp src/Controlador/*.cpp src/Modelo/*.cpp src/Modelo/entidades/*.cpp src/Vista/*.cpp src/Red/*.cpp
OBJS = src/*.cpp

CC = g++

COMPILER_FLAGS = -w -std=c++11 -g

LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2main -lyaml-cpp -lSDL2_ttf

OBJ_NAME = metalslug.out 

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
