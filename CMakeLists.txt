cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_definitions(-std=c++11)

project (Progetto)

include_directories(include)

add_library(Scacchiera
    include/Scacchiera.h
    src/Scacchiera.cpp
)
add_library(Pezzi
    include/Pezzi.h
    src/Pezzi.cpp
)

add_executable (Progetto
    src/main.cpp)

target_link_libraries(Progetto Scacchiera)
target_link_libraries(Progetto Pezzi)


