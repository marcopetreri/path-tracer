cmake_minimum_required(VERSION 3.0)

project(path_tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add_definitions(-g)
# add_definitions(-O0)

# FIND_PACKAGE( OpenMP REQUIRED)
# if(OPENMP_FOUND)
# message("OPENMP FOUND")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

IF(APPLE)
  FIND_LIBRARY(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
  FIND_LIBRARY(OPENGL_LIBRARY NAMES OpenGL)
ENDIF(APPLE)

# Setting some utilities variables
set(EXTERNAL_LIBRARIES_DIR ${CMAKE_CURRENT_LIST_DIR}/externals)

set(RAPIDXML_INCLUDE_DIR ${EXTERNAL_LIBRARIES_DIR}/rapidxml)

include_directories(${RAPIDXML_INCLUDE_DIR})

# Building of SOIL2 library
message(">>--> Add SOIL2 target")

set(SOIL2_DEPS -Wall -lglut -lGL -lGLU)
IF(APPLE)
  set(SOIL2_DEPS ${OPENGL_LIBRARY} ${COREFOUNDATION_LIBRARY})
ENDIF(APPLE)
set(SOIL2_DIR ${EXTERNAL_LIBRARIES_DIR}/SOIL2)
set(SOIL2_INCLUDE_DIR ${SOIL2_DIR}/incs)
set(SOIL2_LIB ${SOIL2_DIR}/libSOIL2${CMAKE_STATIC_LIBRARY_SUFFIX} ${SOIL2_DEPS})

add_custom_target(
  SOIL2
  COMMAND make
  WORKING_DIRECTORY ${SOIL2_DIR}
)

include_directories(${SOIL2_INCLUDE_DIR})

message("<--<< Added SOIL2 target")


# Building of assimp library
message(">>--> Add Assimp target")

set(ASSIMP_DIR ${EXTERNAL_LIBRARIES_DIR}/assimp)
set(ASSIMP_BUILD_DIR ${ASSIMP_DIR}/build)
set(ASSIMP_INCLUDE_DIRS ${ASSIMP_DIR}/include ${ASSIMP_BUILD_DIR}/include)
set(ASSIMP_LIB ${ASSIMP_BUILD_DIR}/code/libassimp${CMAKE_SHARED_LIBRARY_SUFFIX})

set(BUILD_SHARED_LIBS ON CACHE BOOL "Enabled Assimb shared libs build" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disabled Assimp tests build" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Disabled Assimp tools build" FORCE)

add_subdirectory(${ASSIMP_DIR} ${ASSIMP_BUILD_DIR})
add_custom_target(
  ASSIMP
  COMMAND make -j4
  WORKING_DIRECTORY ${ASSIMP_BUILD_DIR}
)

include_directories(${ASSIMP_INCLUDE_DIRS})

message("<--<< Added Assimp target")

# Building of core target
message(">>--> Add Core target")

add_subdirectory(core)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} WORLD ${ASSIMP_LIB} ${SOIL2_LIB})

add_dependencies(${CMAKE_PROJECT_NAME} SOIL2 ASSIMP)

message("<--<< Added Core target")