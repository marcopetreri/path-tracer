# Features libraries folders paths variables

set(GEOMETRY_DIR ${CMAKE_CURRENT_LIST_DIR}/geometry)
set(GEOMETRIC_OBJECTS_DIR ${CMAKE_CURRENT_LIST_DIR}/geometricObjects)
set(CAMERAS_DIR ${CMAKE_CURRENT_LIST_DIR}/cameras)
# set(INTEGRATORS_DIR ${CMAKE_SOURCE_DIR}/core/integrators)
# set(UTILITIES_DIR ${CMAKE_SOURCE_DIR}/core/utilities)
# set(MISC_DIR ${CMAKE_SOURCE_DIR}/core)


# Building libraries

add_library(GEOMETRY SHARED
  ${GEOMETRY_DIR}/mat4f.cpp
  ${GEOMETRY_DIR}/mat4d.cpp
  ${GEOMETRY_DIR}/transform.cpp
)

add_library(GEOMETRIC_OBJECTS SHARED
  ${GEOMETRIC_OBJECTS_DIR}/sphere.cpp
  ${GEOMETRIC_OBJECTS_DIR}/triangle.cpp
)

add_library(CAMERAS SHARED
  ${CAMERAS_DIR}/camera.cpp
  ${CAMERAS_DIR}/orthographic.cpp
  ${CAMERAS_DIR}/perspective.cpp
)

add_library(ACCELERATORS STATIC ${CMAKE_CURRENT_LIST_DIR}/accelerators/accelerator.cpp)

add_library(PARSER STATIC ${CMAKE_CURRENT_LIST_DIR}/utilities/parser.cpp)

add_library(WORLD STATIC ${CMAKE_CURRENT_LIST_DIR}/world.cpp)

# Linking libraries

target_link_libraries(CAMERAS GEOMETRY)

target_link_libraries(PARSER CAMERAS GEOMETRIC_OBJECTS GEOMETRY)

target_link_libraries(WORLD ACCELERATORS PARSER)
