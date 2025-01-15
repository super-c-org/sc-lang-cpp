cmake_minimum_required(VERSION 3.30.0)
project(super_c_compiler VERSION 0.1.0 LANGUAGES C CXX)

# C++ requirements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# LLVM config
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}, build type ${LLVM_BUILD_TYPE}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

llvm_map_components_to_libnames(LLVM_LIBS support core)

# Libraries
add_library(calculator src/calc.cpp)

# Compiler target
add_executable(scc)
target_include_directories(scc PRIVATE
  src
  ${LLVM_INCLUDE_DIRS}
)
target_sources(scc PRIVATE
  src/main.cpp
  src/driver/driver.cpp
)
target_link_libraries(scc PRIVATE
  calculator
  ${LLVM_LIBS}
)

# Testing
find_package(Catch2 3 REQUIRED)

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

#Packing
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
