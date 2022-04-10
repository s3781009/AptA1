cmake_minimum_required(VERSION 3.21)
project(answer)

set(CMAKE_CXX_STANDARD 14)

add_executable(answer main.cpp NodeList.cpp Node.cpp PathPlanner.cpp )
