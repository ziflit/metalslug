cmake_minimum_required(VERSION 3.6)
project(metalslug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread ")

set(SOURCE_FILES
    notas/20160826.txt
    src/model/client.cpp
    src/model/client.h
    src/model/ClientConnection.cpp
    src/model/ClientConnection.h
    src/model/message.cpp
    src/model/message.h
    src/model/server.cpp
    src/model/server.h
    src/model/User.cpp
    src/model/User.h
    src/test/MessagesTests.cpp
    src/Utils/File.cpp
    src/Utils/File.h
    src/Utils/Logger.cpp
    src/Utils/Logger.h
    src/Utils/Protocol.h
    src/Utils/SocketUtils.cpp
    src/Utils/SocketUtils.h
    src/Utils/StringUtil.cpp
    src/Utils/StringUtil.h
    src/client_main.cpp
    src/server_main.cpp
    Makefile
    README.md)

add_executable(metalslug ${SOURCE_FILES})