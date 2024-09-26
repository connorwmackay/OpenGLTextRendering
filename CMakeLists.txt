cmake_minimum_required(VERSION 3.20)
project(TextRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/glad)
    message(SEND_ERROR "libraries/glad/include directory was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/glad/include)
    message(SEND_ERROR "libraries/glad/include directory was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/glad/src/glad.c)
    message(SEND_ERROR "libraries/glad/src/glad.c file was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/GLFW)
    message(SEND_ERROR "libraries/GLFW/include directory was not found")
ENDIF()


IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/GLFW/lib)
    message(SEND_ERROR "libraries/GLFW/lib directory was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/GLFW/lib)
    message(SEND_ERROR "libraries/GLFW/include directory was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/freetype-windows-binaries)
    message(SEND_ERROR "libraries/freetype-windows-binaries directory was not found")
ENDIF()

IF(NOT EXISTS ${CMAKE_SOURCE_DIR}/libraries/freetype-windows-binaries/include)
    message(SEND_ERROR "libraries/freetype-windows-binaries/include directory was not found")
ENDIF()

IF(NOT EXISTS "${CMAKE_SOURCE_DIR}/libraries/freetype-windows-binaries/release static")
    message(SEND_ERROR "libraries/freetype-windows-binaries/include directory was not found")
ENDIF()

IF(NOT EXISTS "${CMAKE_SOURCE_DIR}/libraries/glm")
    message(SEND_ERROR "libraries/glm directory was not found")
ENDIF()

set(SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/glad/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/font.h
)

include_directories(SOURCES)

find_package(OpenGL REQUIRED)

add_executable(TextRenderer ${SOURCES})
target_link_libraries(TextRenderer PUBLIC opengl32 ${CMAKE_SOURCE_DIR}/libraries/GLFW/lib/glfw3.lib "${CMAKE_SOURCE_DIR}/libraries/freetype-windows-binaries/release static/vs2015-2022/win64/freetype.lib")
target_include_directories(TextRenderer PUBLIC ${CMAKE_SOURCE_DIR}/libraries/glad/include ${CMAKE_SOURCE_DIR}/libraries/GLFW/include ${CMAKE_SOURCE_DIR}/libraries/freetype-windows-binaries/include ${CMAKE_SOURCE_DIR}/libraries/glm)