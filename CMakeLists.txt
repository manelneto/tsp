cmake_minimum_required(VERSION 3.25)
project(tsp)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(tsp main.cpp Graph.cpp Graph.h Management.cpp Management.h Vertex.cpp Vertex.h Edge.cpp Edge.h MutablePriorityQueue.h)
