cmake_minimum_required(VERSION 2.8)

project(GraphProj)

#class library
add_library(cartesiansystem STATIC cartesiansystem.cpp)

add_executable(${PROJECT_NAME} main.cpp)

#SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED network audio graphics window system)
target_link_libraries(${PROJECT_NAME} cartesiansystem)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

