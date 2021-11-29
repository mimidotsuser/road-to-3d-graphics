## Road to 3d Graphics (WIP)
I am creating a short game while I learn (modern) OpenGL.

I provide no guarantee of this project working outside Linux at the moment.

## How to set up
#### Ubuntu prerequisites
- Install build tools ``sudo apt-get install build-essential libssl-dev``
- Install CMake ``sudo apt-get install cmake``
- Install make ``sudo apt-get install make``
- Install GCC compiler ``sudo apt-get install gcc``
- Install Mesa OpenGL utility library (GLU) ``sudo apt-get install libglu-dev``
- Install  OpenGL wrangler library (GLEW) ``sudo apt-get install libglew-dev``

_Use `aptitude` if you encounter issues with dependencies while installing GLU or GLEW_

## Build and run
1. Clone the repository ``sh git clone  https://github.com/mimidotsuser/road-to-3d-graphics.git``
2. Enter the directory ``cd road-to-3d-graphics``
2. Make a build directory & enter it ``mkdir build && cd build``.
3. Generate build files ``cmake -DCMAKE_BUILD_TYPE=Debug ../``
4. Build the project ``make all``
5. Run the build output ``./graphics``