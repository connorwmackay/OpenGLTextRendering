@echo off
CD build
cmake ..
CD ..
cmake --build build --config release
start CMD /k "build\release\TextRenderer.exe"
pause