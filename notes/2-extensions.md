## OpenGL Extension Utilities

- Graphics card manufacturers implement the OpenGL standard on their drivers differently. The variation means the functions
  locations are unknown at compile-time, and one has to query them at runtime.
- One can write the logic to retrieve the location of the function and store them in a function pointer for later use
  (on each platform). Luckily, great libraries such as ``GLEW``and ``GLAD``have abstracted such
  cumbersome and tedious tasks.
- This project utilizes the ``GLEW`` library.

**NOTE :** `glew.h` should not be included before ``glfw3.h``. A preprocessor error is raised if `gl.h`, `glext.h`,
or `glATI.h` is included before GLEW

- After creating a rendering context (must happen after making the context current), initialize the glew to load
  available extensions.