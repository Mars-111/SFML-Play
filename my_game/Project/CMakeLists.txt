cmake_minimum_required(VERSION 3.28)
project(my_game)

set(CMAKE_CXX_STANDARD 20)

set(SRC_FILES src/main.cpp src/Game.cpp)
set(HEADERS_FILES headers/Game.h)

add_executable(my_game ${SRC_FILES} ${HEADERS_FILES})

target_include_directories(my_game PUBLIC src headers)


target_link_libraries(my_game PRIVATE
        sfml-graphics
)

file(COPY resources/calibri.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})