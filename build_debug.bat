@echo off
CD build
cmake ..
CD ..
COPY libraries/GLFW/lib/glfw3.dll build\debug\glfw3.dll
cmake --build build --config debug
start CMD /k "build\debug\TextRenderer.exe"
pause