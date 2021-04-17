//
// Created by sriney on 4/9/21.
//

#pragma once

#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>

#include "GLErrorManager.h"

#include "Shader.h"


Shader::Shader(const std::string& filepath)
: m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    std::cout  << std::endl << filepath << std::endl;
    std::cout  << "stream fails: " << stream.fail() << std::endl;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    unsigned int i = 0;
    while(getline(stream, line))
    {
        i++;
        std::cout << std::to_string(i) << line << std::endl;
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        } else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};

}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char) );
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" <<
                  (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    //TODO: Error handling

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string &name, int value)
{
    GLCall(glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        {std::cout << "Warning: Uniform" << name << " with location " << location << std::endl;}
    else
        m_UniformLocationCache[name] = location;
    return location;
}





