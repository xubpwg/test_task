cmake_minimum_required(VERSION 3.10)

# set the project name
project(Task2)

# set all sources as variable
set(SOURCES main.cpp JavaLanguage.cpp CppLanguage.cpp)

# add the executable
add_executable(Task2 ${SOURCES})