# OpenGL Text Rendering
This project currently requires OpenGL 4.5+. You can create a font at a specific font size and all characters drawn using the font will be instanced, meaning one draw call for all text that uses the font.
![showcase](showcase.png)

## Running the project
- You can run ```./build_debug.bat``` to build and run the project in debug mode
- You can run ```./build_release.bat``` to build and run the project in release mode

## Required Dependencies
This project requires GLFW, GLAD, glm, and freetype.
You can find the Freetype windows binaries here: https://github.com/ubawurinna/freetype-windows-binaries

There should be a folder called libraries at the project root. It should look like this:
- freetype-windows-binaries
    - include
    - release static
- GLFW
    - include
    - lib
- glm
- glad
    - include
    - src
        - glad.c
