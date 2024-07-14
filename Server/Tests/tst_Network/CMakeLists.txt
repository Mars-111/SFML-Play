cmake_minimum_required(VERSION 3.28)
project(tst_Network)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

##include tst_Network
set(FILE
        "../../Server/src/Network.cpp"
        "../../Server/headers/Network.h"
)
##

add_executable(
        tst_Network
        tst_Network.cpp
        ${FILE}
)

##include SqlWrapper
target_include_directories(tst_Network PUBLIC "../../Server/src" "../../Server/headers")
##

target_link_libraries(
        tst_Network
        GTest::gtest_main
        sfml-network
)

include(GoogleTest)
gtest_discover_tests(tst_Network)



