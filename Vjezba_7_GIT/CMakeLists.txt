cmake_minimum_required(VERSION 3.30)
project(vjezba7)

set(CMAKE_CXX_STANDARD 20)

# Ovdje dodajemo sve .cpp datoteke koje čine projekt
add_executable(vjezba7
        main.cpp
        Student.cpp
        Course.cpp
)