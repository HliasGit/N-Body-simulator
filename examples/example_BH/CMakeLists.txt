cmake_minimum_required(VERSION 3.20)
project(N-body)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Set default build type to Release.
if(NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DBUILD_TYPE_DEBUG)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include_directories(../../include/)

add_library(NBodyEnvLibrary
../../src/Particle/Particle.cpp
../../src/System/System.cpp
../../src/Functions/Functions.cpp
../../src/Functions/EulerDiscretizer.cpp
../../src/Functions/VerletDiscretizer.cpp
../../src/Exporter/Exporter.cpp
../../src/Collisions/Collisions.cpp
../../src/TreeNode/TreeNode.cpp
../../src/Functions/RKDiscretizer.cpp
)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

add_executable(Example
    ../example_BH/example_BH.cpp
    ${HEADER_FILES}
)

add_executable(BHrandom
    ../example_BH/example_BHrand.cpp
    ${HEADER_FILES}
)

target_compile_options(BHrandom PRIVATE ${OPENMP_FLAGS})

target_link_libraries(Example NBodyEnvLibrary)
target_link_libraries(BHrandom NBodyEnvLibrary OpenMP::OpenMP_CXX)
# target_link_libraries(BHrandom NBodyEnvLibrary)