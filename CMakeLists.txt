add_compile_definitions()
cmake_minimum_required(VERSION 3.30)
project(route_planner)

set(CMAKE_CXX_STANDARD 20)

add_executable(route_planner
        SetUp/DataStructures/Graph.h
        SetUp/DataStructures/MutablePriorityQueue.h
        SetUp/DataStructures/UFDS.h
        SetUp/DataStructures/UFDS.cpp
        SetUp/InputOutput/Input.h
        SetUp/InputOutput/Input.cpp
        SetUp/Main.cpp
        SetUp/Menu/Menu.h
        SetUp/Menu/Menu.cpp
        SetUp/ReadData/readCSV.cpp
        SetUp/ReadData/readCSV.h
        SetUp/Routes/IndependentRoutePlanning.cpp
        SetUp/Routes/IndependentRoutePlanning.h
        SetUp/InputOutput/Output.cpp
        SetUp/InputOutput/Output.h
        SetUp/Routes/RestrictedRoutePlanning.h
        SetUp/Routes/EnvironmentallyFriendlyRoutePlanning.h
        SetUp/Routes/RestrictedRoutePlanning.cpp
        SetUp/Routes/EnvironmentallyFriendlyRoutePlanning.cpp
        SetUp/InputOutput/Visualizer.cpp
        SetUp/InputOutput/Visualizer.h
        SetUp/InputOutput/BatchMode.h
        SetUp/InputOutput/BatchMode.cpp
)
