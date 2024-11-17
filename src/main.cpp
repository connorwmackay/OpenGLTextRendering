#include "font.h"
#include "io.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}


int main(int argc, char **argv) {
    Font::Init();

    File_IO::write_file("assets/save", "{playerHealth: 10}");
    std::cout << File_IO::read_file("assets/save") << "\n";

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    #ifdef _DEBUG
        std::cout << "Running in Debug Mode\n";
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(1366, 768, "Text Renderer", nullptr, nullptr);

    if (!window)
        return -1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        return -1;

    glViewport(0, 0, 1366, 768);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    #ifdef _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
    #endif

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 projection = glm::ortho(0.0f, 1366.0f, 768.0f, 0.0f, 10.0f, -10.0f);
    glm::mat4 view = glm::mat4(1.0f);

    Shader textShader = Shader("assets/text.vert", "assets/text.frag");
    Font font = Font("assets/arial.ttf", 48);

    int width = 0, height = 0;
    while (!glfwWindowShouldClose(window)) {
        int curWidth, curHeight;
        glfwGetWindowSize(window, &curWidth, &curHeight);
        if (curWidth != width || curHeight != height) {
            glViewport(0, 0, curWidth, curHeight);
            width = curWidth;
            height = curHeight;
        }

        glfwPollEvents();

        // Render Loop
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Start Rendering Text
        glUseProgram(textShader.getProgram());
            glUniformMatrix4fv(glGetUniformLocation(textShader.getProgram(), "viewProjection"), 1, GL_FALSE, glm::value_ptr(projection * view));

            font.DrawText("Hello, World!", glm::vec2(32, 32), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f);
            font.DrawText("Another text example :)", glm::vec2(128, 128), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);

            // Renders All Text Called via DrawText()
            font.RenderText();
        glUseProgram(0);

        // Swap Buffers
        glfwSwapBuffers(window);
    }

    FT_Done_FreeType(library);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}