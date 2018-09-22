# Path tracer written in C++

A simple rendering engine written in C++ that implements _Monte Carlo Path Tracing_ technique.

## Compatibility

As far as I know it only runs on Linux (ubuntu).

## Requirements

Before building the project make sure you install OpenGL dev suite.

`sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev`

## Building

**IMPORTANT**: because the project has some submodule, add `--recurse-submodules` when cloning it.

From the root of the project, type this commands in order to build it.

`mkdir build && cd build`

`cmake ..`

`make`

## Usage

From the building folder launch the program with the path of a scene for render it.

`./path_tracer ../scenes/SCENE_NAME`

The program outputs its render in the building folder as `rendering.bmp`
