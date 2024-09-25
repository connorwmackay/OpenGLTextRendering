@echo off
CD build
cmake ..
CD ..
cmake --build build --config release
build\release\TextRenderer.exe