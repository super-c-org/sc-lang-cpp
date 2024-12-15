cmake_minimum_required(VERSION 3.30.0)
project(super-c VERSION 0.1.0 LANGUAGES C CXX)

# C++ requirements
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# target: compiler
add_executable(super-c)
target_include_directories(super-c PRIVATE
  src
        )
target_sources(super-c PRIVATE
  src/main.cpp)
target_link_libraries(super-c PRIVATE
 )

# testing
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)
enable_testing()

add_executable(sc-tests test_calc.cpp)
target_include_directories(sc-tests PRIVATE
  src
)
target_link_libraries(sc-tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(sc_tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
