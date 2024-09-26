#ifndef SHADER_H
#define SHADER_H

#include "io.h"
#include <glad/glad.h>

class Shader {
    public:
        Shader(const std::string& vertex_file_name, const std::string& fragment_file_name) {
            const char* vertex_data = File_IO::read_file(vertex_file_name).c_str();
            const char* fragment_data = File_IO::read_file(fragment_file_name).c_str();

            program = glCreateProgram();

            GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_data, nullptr);
            glCompileShader(vertex_shader);

            GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_data, nullptr);
            glCompileShader(fragment_shader);

            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
        }

        const GLuint& getProgram() const {
            return program;
        }

        ~Shader() {
            glDeleteProgram(program);
        }
    private:
        GLuint program;
};

#endif