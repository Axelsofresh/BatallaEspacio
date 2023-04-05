cmake_minimum_required(VERSION 3.25)
project(Escritorio)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio)

add_executable(Escritorio Model/main.cpp Model/main.cpp)

target_link_libraries(Escritorio sfml-graphics sfml-audio)