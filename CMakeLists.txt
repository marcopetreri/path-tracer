cmake_minimum_required(VERSION 3.0)

project(path_tracer)

add_definitions(-std=c++11 -fopenmp)
add_definitions(-g)
# add_definitions(-O0)

# FIND_PACKAGE( OpenMP REQUIRED)
# if(OPENMP_FOUND)
# message("OPENMP FOUND")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

# Setting some utilities variables
set(EXTERNAL_LIBRARIES_DIR ${CMAKE_CURRENT_LIST_DIR}/externals)

# Building of SOIL2
set(SOIL2_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/SOIL2)
set(SOIL2_INCLUDE_DIR ${SOIL2_DIR}/incs)
set(SOIL2_LIB ${SOIL2_DIR}/libSOIL2.a -Wall -lglut -lGL -lGLU)

add_custom_target(
  SOIL2
  COMMAND make
  WORKING_DIRECTORY ${SOIL2_DIR}
)

include_directories(${SOIL2_INCLUDE_DIR})


FIND_PATH(ASSIMP_INCLUDE_DIR NAMES assimp)

message("Assimp include dir: " ${ASSIMP_INCLUDE_DIR})

include_directories(${ASSIMP_INCLUDE_DIR})


add_subdirectory(core)


add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} WORLD)

add_dependencies(${CMAKE_PROJECT_NAME} SOIL2)