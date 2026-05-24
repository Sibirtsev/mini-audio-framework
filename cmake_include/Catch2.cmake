include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(maf_tests
 "tests/utils/MathTests.cpp"
 "tests/core/OwnedAudioBufferTests.cpp"
 "tests/core/AudioBufferViewTests.cpp")

target_link_libraries(maf_tests
    PRIVATE
        maf_core
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(maf_tests)
