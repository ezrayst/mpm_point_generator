project(mpm_point_generator LANGUAGES CXX)

# Require C++11-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE On)
SET(CMAKE_VERBOSE_MAKEFILE Off)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "Debug")
 #SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU Specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fpic")
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# executable
SET(mpm_point_gen_src
    src/main.cpp
)
add_executable(mpm_point_generator
               ${mpm_point_gen_src}
)

# Unit test
SET(test_src
  ${PROJECT_SOURCE_DIR}/tests/test.cc
  ${PROJECT_SOURCE_DIR}/tests/point_test.cc
)   
add_executable(mpm_point_generator_test
	       ${test_src}
)
add_test(NAME mpm_point_generator_test COMMAND $<TARGET_FILE:mpm_point_generator_test>)
enable_testing()
