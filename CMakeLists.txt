cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
        setup/Graph.h
        setup/MutablePriorityQueue.h
        setup/UFDS.h
        setup/UFDS.cpp
        setup/Input.h
        setup/Input.cpp
        SetUp/main.cpp
        SetUp/Menu.h
        SetUp/Menu.cpp
        SetUp/Map.h
        SetUp/Map.cpp)
