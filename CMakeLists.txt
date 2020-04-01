cmake_minimum_required(VERSION 3.15)
project(crapsAgain)

set(CMAKE_CXX_STANDARD 17)

add_executable(crapsAgain crapsGame.cpp die.cpp craps.cpp craps.h)