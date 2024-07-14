cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES src/main.cpp src/Network.cpp src/SqlWrapper.cpp src/Server.cpp src/NetworkEvent.cpp )
set(HEADERS_FILES headers/Network.h headers/SqlWrapper.h headers/Server.h headers/NetworkEvent.h)

add_executable(Server ${SRC_FILES})

target_include_directories(Server PUBLIC src headers)

target_link_libraries(Server PRIVATE
        sfml-network
        SQLiteCpp
        SQLite::SQLite3
)