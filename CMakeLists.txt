cmake_minimum_required(VERSION 3.30.0)
project(scc VERSION 0.1.0 LANGUAGES C CXX)

# C++ requirements
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# for test purpose
add_library(calculator src/calc.cpp)

# target: compiler
add_executable(scc)
target_include_directories(scc PRIVATE
  src
)
target_sources(scc PRIVATE
  src/main.cpp)
target_link_libraries(scc PRIVATE
  calculator
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

add_executable(sc_test)
target_include_directories(sc_test PRIVATE
  src
)
target_sources(sc_test PRIVATE
  src/calc_test.cpp
)
target_link_libraries(sc_test PRIVATE 
  calculator
  Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(sc_test)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
