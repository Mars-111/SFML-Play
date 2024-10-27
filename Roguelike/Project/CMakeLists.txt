cmake_minimum_required(VERSION 3.28)
project(Roguelike)

set(CMAKE_CXX_STANDARD 20)

set(SRC_FILES src/main.cpp src/Object.cpp src/Player.cpp src/MySprite.cpp)
set(HEADERS_FILES headers/Object.h headers/Player.h headers/MySprite.h)

add_executable(Roguelike ${SRC_FILES} ${HEADERS_FILES})

target_include_directories(Roguelike PUBLIC src headers)


target_link_libraries(Roguelike PRIVATE
        sfml-graphics
)

file(COPY resources/calibri.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})