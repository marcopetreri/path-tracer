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

# Building of SOIL2 library
set(SOIL2_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/SOIL2)
set(SOIL2_INCLUDE_DIR ${SOIL2_DIR}/incs)
set(SOIL2_LIB ${SOIL2_DIR}/libSOIL2.so -Wall -lglut -lGL -lGLU)

message("|==> Building SOIL2")
add_custom_target(
  SOIL2
  COMMAND make
  WORKING_DIRECTORY ${SOIL2_DIR}
)
message("<==| SOIL2 builded")

include_directories(${SOIL2_INCLUDE_DIR})

# Building of assimp library
set(ASSIMP_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/assimp)
set(ASSIMP_BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/assimp/build)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_DIR}/include)
set(ASSIMP_LIB ${ASSIMP_BUILD_DIR}/code/libassimp.so.4)

message("|==> Building ASSIMP")
add_subdirectory(${ASSIMP_DIR} ${ASSIMP_BUILD_DIR})
add_custom_target(
  ASSIMP
  COMMAND make
  WORKING_DIRECTORY ${ASSIMP_BUILD_DIR}
)
message("<==| ASSIMP builded")

include_directories(${ASSIMP_INCLUDE_DIR})

message("|==> Building CORE")

add_subdirectory(core)


add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} WORLD)

add_dependencies(${CMAKE_PROJECT_NAME} SOIL2 ASSIMP)

message("<==| CORE builded")