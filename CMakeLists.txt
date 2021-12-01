cmake_minimum_required(VERSION 3.20)
project(SquidGameDS1)

set(CMAKE_CXX_STANDARD 14)

add_executable(SquidGameDS1 library1.h main1.cpp library1.cpp library1.h BinarySearchTree.cpp BinarySearchTree.h Group.cpp Group.h Player.cpp Player.h SquidGame.cpp SquidGame.h)
