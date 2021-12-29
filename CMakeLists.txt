cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_definitions(-std=c++11)

project (Progetto)

include_directories(include)

add_library(ScacchieraL
    include/Scacchiera.h
    src/Scacchiera.cpp
)
add_library(PezziL
    include/Scacchiera.h
    include/Pezzi.h
    src/Pedina.cpp
    src/Pezzi.cpp
)

add_executable (Scacchiera
    src/Gioco.cpp)

add_executable (Replay
    src/Replay.cpp)

target_link_libraries(Scacchiera ScacchieraL)
target_link_libraries(Scacchiera PezziL)


