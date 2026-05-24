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
 "src/utils/Math.cpp" 
 "include/maf/core/OwnedAudioBuffer.tpp"
 "include/maf/core/AudioBufferView.tpp")

target_include_directories(maf_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(maf_core
    PUBLIC
        cxx_std_20
)

target_compile_definitions(maf_core
    PUBLIC
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:RelWithDebInfo>:NDEBUG>
        $<$<CONFIG:MinSizeRel>:NDEBUG>
)

if(MSVC)
    target_compile_options(maf_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(maf_core PRIVATE -Wall -Wextra -Wpedantic)
endif()


add_executable(maf_hello 
 "src/hello.cpp" 
 "include/maf/core/Hello.h" 
 "src/core/Hello.cpp" 
 "include/maf/utils/Math.h" 
 "src/utils/Math.cpp" 
 "include/maf/core/OwnedAudioBuffer.h"
 "include/maf/core/AudioBufferView.h"
)

target_link_libraries(maf_hello
    PRIVATE
        maf_core
)

enable_testing()

include(cmake_include/Catch2.cmake)
