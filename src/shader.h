#ifndef SHADER_H
#define SHADER_H

#include "io.h"
#include <glad/glad.h>

class Shader {
    GLuint program;

    public:
        Shader() {}

        Shader(const std::string& vertex_file_name, const std::string& fragment_file_name) {
            std::string vertex_data_str = File_IO::read_file(vertex_file_name);
            std::string fragment_data_str = File_IO::read_file(fragment_file_name);

            const char* vertex_data = vertex_data_str.c_str();
            const char* fragment_data = fragment_data_str.c_str();

            program = glCreateProgram();

            GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_data, nullptr);
            glCompileShader(vertex_shader);

            #ifdef _DEBUG
                char info_log[512];
                int success;
                glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(vertex_shader, 512, nullptr, &info_log[0]);
                    std::cout << "Vertex Shader Error (" << vertex_file_name << "): " << info_log << "\n"; 
                }
            #endif

            GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_data, nullptr);
            glCompileShader(fragment_shader);

            #ifdef _DEBUG
                glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(fragment_shader, 512, nullptr, &info_log[0]);
                    std::cout << "Fragment Shader Error (" << fragment_file_name << "): " << info_log << "\n"; 
                }
            #endif

            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);

            #ifdef _DEBUG
                glGetProgramiv(program, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(program, 512, nullptr, &info_log[0]);
                    std::cout << "Program Linking Error (" << vertex_shader << "), (" << fragment_file_name << "): " << info_log << "\n";
                }
            #endif

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
        }

        const GLuint& getProgram() const {
            return program;
        }

        ~Shader() {
            glDeleteProgram(program);
        }    
};

#endif