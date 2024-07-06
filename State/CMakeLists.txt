cmake_minimum_required(VERSION 3.16.3)

project(state)

add_executable (state main.cpp )
target_link_libraries (state ${state_LIBRARIES} )