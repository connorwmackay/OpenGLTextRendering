#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Text Renderer", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}