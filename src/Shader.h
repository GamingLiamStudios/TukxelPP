#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>

#define NULL 0

class Shader {
public:
	unsigned int ID;
	
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
        int success;
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
            return;
        }

        //Delete Vertex & Fragment Shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
	}
	
    void use() {
        glUseProgram(ID);
    }
	
    void setBool(const std::string& name, bool value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
};