cmake_minimum_required(VERSION 3.0)

project(path_tracer)

add_definitions(-std=c++11 -fopenmp)
add_definitions(-g)
# add_definitions(-O0)

# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

# find_package(ASSIMP REQUIRED)
# include_directories(${ASSIMP_INCLUDE_DIRS})

# find_package(SOIL REQUIRED)
# include_directories(${SOIL_INCLUDE_DIRS})

# FIND_PACKAGE( OpenMP REQUIRED)
# if(OPENMP_FOUND)
# message("OPENMP FOUND")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

FIND_PATH(ASSIMP_INCLUDE_DIR NAMES assimp)
FIND_PATH(SOIL_INCLUDE_DIR NAMES SOIL)

message("Assimp include dir: " ${ASSIMP_INCLUDE_DIR})
message("Soil include dir: " ${SOIL_INCLUDE_DIR})

include_directories(ASSIMP_INCLUDE_DIR)
include_directories(SOIL_INCLUDE_DIR)

add_subdirectory(core)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} WORLD)
