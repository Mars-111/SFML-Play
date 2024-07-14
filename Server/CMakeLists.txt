cmake_minimum_required(VERSION 3.28)
project(Server)

set(CMAKE_CXX_STANDARD 17)

#SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:\\SFML-2.6.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 REQUIRED network)

add_subdirectory(libraries/SQLiteCpp)

add_subdirectory(Server)

add_subdirectory(Tests)