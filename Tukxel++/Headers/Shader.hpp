#pragma once
#ifndef SHADERH
#define SHADERH

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>

class Shader {
public:
	unsigned int ID;
    int success;

    Shader() {}
	
	Shader(const char* vertexPath, const char* fragmentPath) {
        //Create Vertex & Fragment Shaders
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //Read Vertex & Fragment Shaders
        std::ifstream vertex(vertexPath); std::ifstream fragment(fragmentPath);
        if (!vertex || !fragment) {
            std::cout << "Unable to open File/s" << std::endl;
            return;
        }
        std::string vertexContent((std::istreambuf_iterator<char>(vertex)), (std::istreambuf_iterator<char>()));
        std::string fragmentContent((std::istreambuf_iterator<char>(fragment)), (std::istreambuf_iterator<char>()));
        const char* vp = vertexContent.c_str(); const char* fp = fragmentContent.c_str();

        //Compile Vertex Shader
        glShaderSource(vertexShader, 1, &vp, NULL);
        glCompileShader(vertexShader);
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                infoLog << std::endl;
            return;
        }
        vertex.close();

        //Compile Fragment Shader
        glShaderSource(fragmentShader, 1, &fp, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
                infoLog << std::endl;
            return;
        }
        fragment.close();

        //Create Shader Program and Attach Vertex & Fragment Shaders
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
                infoLog << std::endl;
            glDeleteProgram(ID);
        }

        //Delete Vertex & Fragment Shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
	}
	
    void use() {
        glUseProgram(ID);
    }
	
    void setBool(const char* name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name), (int)value);
    }

    void setInt(const char* name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name), value);
    }

    void setFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name), value);
    }

    void setVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
    }
    void setVec2(const char* name, float x, float y) const {
        glUniform2f(glGetUniformLocation(ID, name), x, y);
    }

    void setVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
    }

    void setVec3(const char* name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name), x, y, z);
    }

    void setVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
    }
    void setVec4(const char* name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
    }

    void setMat2(const char* name, const glm::mat2& mat) const {
        glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const char* name, const glm::mat3& mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const char* name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
    }
};
#endif