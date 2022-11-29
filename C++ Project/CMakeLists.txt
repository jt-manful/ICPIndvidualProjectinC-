cmake_minimum_required(VERSION 3.22)
project(C___Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(C___Project
        airline.cpp
        Airport.cpp
        Routes.cpp
        Routes.h
        main.cpp Graph.cpp Graph.h Vertex.cpp Vertex.h Edge.cpp Edge.h)
