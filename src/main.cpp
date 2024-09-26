#include "font.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    Font::init();
    Font font = Font("assets/MinimalPixelFont.ttf", 16);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Text Renderer", nullptr, nullptr);

    if (!window)
        return -1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        return -1;

    glViewport(0, 0, 1280, 720);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        font.draw_text("Hello, World", 32, 32);

        glfwSwapBuffers(window);
    }
    

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}