cmake_minimum_required(VERSION 3.28)
project(Roguelike)

set(CMAKE_CXX_STANDARD 20)

#SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_DIR "C:\\SFML-2.6.1\\lib\\cmake\\SFML")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics)

add_subdirectory(Project)
