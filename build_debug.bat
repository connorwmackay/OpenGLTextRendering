@echo off
CD build
cmake ..
CD ..
cmake --build build --config debug
build\debug\TextRenderer.exe
pause