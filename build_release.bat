@echo off
CD build
cmake ..
CD ..
MKDIR ".\build\release\assets"
XCOPY ".\assets" ".\build\release\assets" /Y
XCOPY ".\libraries\GLFW\lib\glfw3.dll" ".\build\release" /Y
cmake --build build --config release
start CMD /k "build\release\TextRenderer.exe"
pause