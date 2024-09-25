cmake_minimum_required(VERSION 3.20)
project(TextRenderer LANGUAGES CXX)

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

set(EXTERNAL 
    libraries/glad/src/glad.c
)

set(SOURCES 
    src/main.cpp
)

include_directories(SOURCES)

find_package(OpenGL REQUIRED)

add_executable(TextRenderer ${SOURCES})
target_link_libraries(TextRenderer PUBLIC opengl32 ${CMAKE_SOURCE_DIR}/libraries/GLFW/lib/glfw3.lib)
target_include_directories(TextRenderer PUBLIC ${CMAKE_SOURCE_DIR}/libraries/glad/include ${CMAKE_SOURCE_DIR}/libraries/GLFW/include)