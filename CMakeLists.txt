cmake_minimum_required(VERSION 3.20)

project(MiniAudioFramework
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(maf_core STATIC
    src/core/Hello.cpp
)

target_include_directories(maf_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(maf_core
    PUBLIC
        cxx_std_20
)

if(MSVC)
    target_compile_options(maf_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(maf_core PRIVATE -Wall -Wextra -Wpedantic)
endif()


add_executable(maf_hello src/hello.cpp "include/maf/core/Hello.h" "src/core/Hello.cpp")

target_link_libraries(maf_hello
    PRIVATE
        maf_core
)

enable_testing()

add_executable(maf_core_tests
    tests/core/HelloTests.cpp
)

target_link_libraries(maf_core_tests
    PRIVATE
        maf_core
)

add_test(NAME maf_core_tests COMMAND maf_core_tests)
