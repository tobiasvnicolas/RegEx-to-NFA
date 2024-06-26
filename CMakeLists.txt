cmake_minimum_required(VERSION 3.10)
project(RegexNFA CXX)  # Especifica el lenguaje C++

set(CMAKE_CXX_STANDARD 17)

# Incluye directamente el archivo json.hpp en el proyecto
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${JSON_INCLUDE_DIR})

# Establece la ruta al compilador MinGW
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

# Agrega el archivo main.cpp al proyecto
add_executable(RegexNFA main.cpp)