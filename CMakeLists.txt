cmake_minimum_required(VERSION 2.8)
project(numc)

include_directories(include)
set(NUMC_HDRS include/numc.h)

# ADD NUMC LIBRARY
add_subdirectory(src)

# ADD TESTS
include(CTest)
if(${BUILD_TESTING})
  enable_testing()
  SET(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

  add_subdirectory(lib)
  add_subdirectory(test)
endif()
