cmake_minimum_required(VERSION 4.0 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(playground
    VERSION 0.1.0
    DESCRIPTION "The 'playground' program."
    LANGUAGES CXX
)



add_executable(playground
    playground.h
    playground.cxx
    main.cxx
)
#
target_include_directories(playground PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_dependencies(playground logbook)

#
target_link_libraries(playground  sqlite3  logbook)
#
#
