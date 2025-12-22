cmake_minimum_required(VERSION 3.10.0)
project(binary_tree_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

add_library(bst STATIC BinarySearchTree.cpp)

target_include_directories(bst PUBLIC ${CMAKE_SOURCE_DIR}/)

add_executable(binary_tree_test main.cpp)

target_link_libraries(binary_tree_test PRIVATE bst)
