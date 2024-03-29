cmake_minimum_required(VERSION 3.20)
project(N-body)

set(CMAKE-CXX-STANDARD 20)
set(CMAKE-CXX-FLAGS "${CMAKE-CXX-FLAGS} -Wall")

# Set default build type to Release.
if(NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DBUILD_TYPE_DEBUG)
endif()
message(STATUS)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS)

# Include Boost Library for mk modules
add_compile_options(-O3 -funroll-all-loops -I$ENV{mkBoostInc} -L$ENV{mkBoostLib} -lboost_iostreams -lboost_serialization)

# MPI
find_package(MPI REQUIRED)
# openMPI
add_definitions(-DOMPI_SKIP_MPICXX)
#OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

# Project declaration
project(n-body-sim VERSION 1.0.0 DESCRIPTION "A library for n-body simulation")

# Library files
add_library(n-body-sim STATIC
    src/Collisions/Collisions.cpp
    src/Collisions/CubeBoundary.cpp
    src/Collisions/SphereBoundary.cpp
    src/Exporter/Exporter.cpp
    src/Functions/EulerDiscretizer.cpp
    src/Functions/Functions.cpp
    src/Functions/RKDiscretizer.cpp
    src/Functions/VerletDiscretizer.cpp
    src/Particle/Particle.cpp
    src/Simulator/Simulator.cpp
    src/System/System.cpp
    src/TreeNode/TreeNode.cpp
)

# Version property
set_target_properties(n-body-sim PROPERTIES VERSION ${PROJECT_VERSION})

# Include directory
target_include_directories(n-body-sim PRIVATE include)

target_link_libraries(n-body-sim OpenMP::OpenMP_CXX)

