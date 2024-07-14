cmake_minimum_required(VERSION 3.28)
project(tst_SqlWrapper)

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

##include SqlWrapper
set(FILE_SQLWRAPPER
        "../../Server/src/SqlWrapper.cpp"
        "../../Server/headers/SqlWrapper.h"
)
##

add_executable(
        tst_SqlWrapper
        tst_SqlWrapper.cpp
        ${FILE_SQLWRAPPER}
)

##include SqlWrapper
target_include_directories(tst_SqlWrapper PUBLIC "../../Server/src" "../../Server/headers")
##

target_link_libraries(
        tst_SqlWrapper
        GTest::gtest_main
        SQLiteCpp
        SQLite::SQLite3
)

include(GoogleTest)
gtest_discover_tests(tst_SqlWrapper)



