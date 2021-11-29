## Introduction

- OpenGL is a specification, and thus feature support or implementation may differ
- OpenGL is essentially a state machine. By minimum, to render a graphic on a window,

1. Set aside memory to store the graphic data
2. Define the graphic data organization for processing
3. Set the logic on how to render the graphics on a window
4. Clear the window, and call the rendering logic

OpenGL provides various functions to manipulate the current state
(commonly referred to as OpenGL context) through creation and modification of memory buffers.

Primarily, OpenGL >+ 3.6 workflow generally has the following steps:

1) Create an identifier in the CPU
2) Create a memory object on the VRAM and assign it to the above identifier
3) Bind the memory object to a target context, e.g., a window, a flag e.t.c
4) Set the options for the bound object
5) Modify the data of the bound object

## Window

- Before one draws something, an OpenGL context and a window are required. There is no specification on how to create
  one, thus libraries' implementation may differ.
- My implementation utilizes ``GLFW``. All that is required is:
  - Initialize the GL
  - Create a window
  - Set the window as the current context

The above logic will display a window for a few milliseconds and exit. An event/render loop is required to draw
any graphics and listen for user events continuously. At a bare minimum, the event loop should continuously poll window events and
swap buffers after each draw.

**NOTE:** _As drawing is not instant, i.e., it is done pixel by pixel, most modern windows utilize
double buffer to avoid flickering. A front buffer includes an image currently shown on the screen, while a back buffer
includes rendering commands for the next draw. Once the rendering commands finalize, a swap occurs._

- Remember to clean up GLFW's resources on context termination.
- Running the above logic will produce a blank window.