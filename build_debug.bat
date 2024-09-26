@echo off
CD build
cmake ..
CD ..
MKDIR ".\build\debug\assets"
XCOPY ".\assets" ".\build\debug\assets" /Y
XCOPY ".\libraries\GLFW\lib\glfw3.dll" ".\build\debug" /Y
cmake --build build --config debug
start CMD /k "build\debug\TextRenderer.exe"
pause