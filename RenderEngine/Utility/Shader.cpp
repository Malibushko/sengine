#include "Shader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace {
std::string readfile(const char* name)
{
    std::ifstream stream(name);
    if(!stream.is_open())
    {
        std::cerr << "Cannot open file " << name << "\n";
        return {};
    }
    std::string buff;
    buff.resize(std::filesystem::file_size(name));
    stream.read(buff.data(), buff.size());
    return buff;
}
bool check_error(int descr, int error = GL_COMPILE_STATUS)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(descr, error, &success);
    if(!success)
    {
        glGetShaderInfoLog(descr, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}
} // namespace

Shader::Shader(std::string_view vertex, std::string_view fragment)
{
    std::string vertexCode = readfile(vertex.data());
    std::string fragmentCode = readfile(fragment.data());
    char*       innerVertexData = vertexCode.data();
    char*       innerFragmentData = fragmentCode.data();

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_VertexShader, 1, &innerVertexData, nullptr);
    glShaderSource(m_FragmentShader, 1, &innerFragmentData, nullptr);

    glCompileShader(m_VertexShader);
    glCompileShader(m_FragmentShader);

    if(!check_error(m_VertexShader) || !check_error(m_FragmentShader))
    {
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, m_VertexShader);
    glAttachShader(m_ID, m_FragmentShader);
    glLinkProgram(m_ID);
}

Shader::~Shader()
{
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shader::Use() const
{
    glUseProgram(m_ID);
}

bool Shader::IsValid() const
{
    return m_ID > 0 && m_VertexShader > 0 && m_FragmentShader > 0;
}

unsigned int Shader::GetId() const
{
    return m_ID;
}

void Shader::Set(std::string_view name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.data()), value);
}

void Shader::Set(std::string_view name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.data()), value);
}

void Shader::Set(std::string_view name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.data()), value);
}

void Shader::Set(std::string_view name, double value) const
{
    Set(name, static_cast<float>(value));
}

void Shader::Set(std::string_view name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(m_ID, name.data()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Set(std::string_view name, const glm::vec3& vec) const
{
    Set(name, vec.x, vec.y, vec.z);
}

void Shader::Set(std::string_view name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_ID, name.data()), x, y, z);
}
