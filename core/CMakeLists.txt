set(ACCELERATORS ${CMAKE_SOURCE_DIR}/core/accelerators)
set(CAMERAS ${CMAKE_SOURCE_DIR}/core/cameras)
set(GEOMETRICOBJECTS ${CMAKE_SOURCE_DIR}/core/geometricObjects)
set(GEOMETRY ${CMAKE_SOURCE_DIR}/core/geometry)
set(INTEGRATORS ${CMAKE_SOURCE_DIR}/core/integrators)
set(UTILITIES ${CMAKE_SOURCE_DIR}/core/utilities)
set(MISC ${CMAKE_SOURCE_DIR}/core)

set(accelerators accelerator)
set(cameras camera orthographic perspective)
set(geometricObjects sphere triangle)
set(geometry mat4f mat4d transform)
set(utilities parser)
set(misc world)

foreach(file ${accelerators})
  add_library(${file} ${ACCELERATORS}/${file}.cpp)
endforeach(file)

foreach(file ${cameras})
  add_library(${file} ${CAMERAS}/${file}.cpp)
endforeach(file)

foreach(file ${geometry})
  add_library(${file} ${GEOMETRY}/${file}.cpp)
endforeach(file)

foreach(file ${geometricObjects})
  add_library(${file} ${GEOMETRICOBJECTS}/${file}.cpp)
endforeach(file)

foreach(file ${utilities})
  add_library(${file} ${UTILITIES}/${file}.cpp)
endforeach(file)

foreach(file ${misc})
  add_library(${file} ${MISC}/${file}.cpp)
endforeach(file)

target_link_libraries(orthographic camera mat4f)

target_link_libraries(perspective camera mat4f)

target_link_libraries(transform mat4d)

target_link_libraries(parser orthographic perspective transform triangle sphere ${ASSIMP_LIBRARIES})

target_link_libraries(world accelerator parser ${SOIL_LIBRARIES})
