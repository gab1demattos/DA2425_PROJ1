add_compile_definitions()
cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
        SetUp/Graph.h
        SetUp/MutablePriorityQueue.h
        SetUp/UFDS.h
        SetUp/UFDS.cpp
        SetUp/Input.h
        SetUp/Input.cpp
        SetUp/Main.cpp
        SetUp/Menu.h
        SetUp/Menu.cpp
        SetUp/Routes.h
        SetUp/readCSV.cpp
        SetUp/readCSV.h
        SetUp/IndependentRoutePlanning.cpp
        SetUp/IndependentRoutePlanning.h
        SetUp/Output.cpp
        SetUp/Output.h
)
