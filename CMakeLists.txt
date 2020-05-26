cmake_minimum_required(VERSION 3.16)
project(g2 C)

set(CMAKE_C_STANDARD 11)

add_executable(g2 main.c edgeList.c edgeList.h graph.c graph.h que.c que.h stack.c stack.h linkedList.c linkedList.h)