# Para el cliente
#SRC_FILES = src/client_main.cpp $(filter-out src/model/server.cpp, $(wildcard src/model/*.cpp)) $(filter-out src/model/ClientConnection.cpp, $(wildcard src/model/*.cpp)) src/utils/*.cpp
SRC_FILES = src/client_main.cpp src/utils/*.cpp src/model/client.cpp  src/model/User.cpp src/model/ClientHandler.cpp  src/view/SDL/SpritesClasses.cpp src/view/SDL/SDLRunningGame.cpp src/view/SDL/InitialWindow.cpp src/view/SDL/Music.cpp src/view/SDL/Sound.cpp
INC_FILES = src/model/client.h  src/model/User.h src/utils/*.h src/model/ClientHandler.h src/model/Configs.h src/view/SDL/SpritesClasses.h src/view/SDL/InitialWindow.h src/view/SDL/Music.h src/view/SDL/Sound.h
#INC_FILES = src/*.h -I$(filter-out src/model/server.h, $(wildcard src/model/*.h))
OBJ_NAME = client
CLIENT_DEP =

# Para el server
#SRV_SRC_FILES = $(filter-out src/model/client.cpp, $(wildcard src/model/*.cpp)) $(filter-out src/model/ClientHandler.cpp, $(wildcard src/model/*.cpp)) src/server_main.cpp
SRV_SRC_FILES = src/model/server.cpp src/model/ClientConnection.cpp  src/model/UserLoader.cpp src/model/User.cpp src/utils/Logger.cpp \
src/utils/SocketUtils.cpp src/utils/MessageUtils.cpp src/server_main.cpp
#SRV_SRC_FILES = src/model/server.cpp src/server_main.cpp
# SRV_INC = src/model/server.h $(filter-out src/utils/loremIpsum.cpp, $(wildcard src/utils/*.cpp)) $(filter-out src/utils/User.cpp, $(wildcard src/utils/*.cpp))
SRV_INC = src/model/server.h # src/model/ClientConnection.h src/model/UserLoader.h src/utils/SocketUtils.h src/utils/Protocol.h src/model/User.h
SRV_DEP = -pthread
SRV_OBJ_NAME = server

# Para test
TEST_SRC_FILES = test/*.cpp src/model/*.cpp src/utils/*.cpp
TEST_INC_FILES = src/model/*.h src/utils/*.h
OBJ_NAME_TEST = run-tests

# General
CC = g++
COMPILER_FLAGS = -w -std=c++11 -ggdb -Wall #`pkg-config --cflags --libs sdl2`
LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2_mixer


all : client

client : $(SRC_FILES)
	$(CC) -I$(INC_FILES) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

server : $(SRV_SRC_FILES)
	$(CC) -I$(SRV_INC) $(SRV_SRC_FILES) $(SRV_DEP) $(COMPILER_FLAGS) -o $(SRV_OBJ_NAME)

test : $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(TEST_SRC_FILES) -I$(TEST_INC_FILES) $(COMPILER_FLAGS) -lgtest -o $(OBJ_NAME_TEST)
