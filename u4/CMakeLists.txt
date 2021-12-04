cmake_minimum_required(VERSION 3.12)
project(Project VERSION 1.0.0)

add_executable(
    main
    src/main.c
)

add_library(
 main_lib lib/stdmain.h lib/stdmain.c 
)

target_link_libraries(
    main PRIVATE main_lib
)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    test_main
    test/test_main.cpp
)

target_link_libraries(
    test_main
    main_lib
    gtest_main
)


include(GoogleTest)
gtest_discover_tests(test_main)
