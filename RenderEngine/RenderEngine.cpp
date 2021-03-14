#include "RenderEngine.h"
#include <tbb/parallel_for_each.h>

#include "Utility/Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace details {
enum class SHADER_NAME
{
    LINE_SHADER_VERTEX,
    LINE_SHADER_FRAGMENT,
};
const char* GetShaderPath(SHADER_NAME _Name)
{
    switch(_Name)
    {
    case SHADER_NAME::LINE_SHADER_VERTEX:
        return "LineShader.vert";
    case SHADER_NAME::LINE_SHADER_FRAGMENT:
        return "LineShader.frag";
    }
    return "";
}
} // namespace details

RenderEngine::RenderEngine()
{
}

void RenderEngine::DrawLine(float _BeginX, float _BeginY, float _EndX, float _EndY)
{
    m_RenderCommands.emplace_back([&]() {
        using namespace details;
        Shader LineShader(GetShaderPath(SHADER_NAME::LINE_SHADER_VERTEX),
            GetShaderPath(SHADER_NAME::LINE_SHADER_FRAGMENT));

        if(!LineShader.IsValid())
            return;

        float Vertices[] = {_BeginX, _BeginY, 0, _EndX, _EndY, 0};

        unsigned int VAO = 0;
        unsigned int VBO = 0;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        LineShader.Use();
        glDrawArrays(GL_LINES, 0, 2);
    });
}

void RenderEngine::ProcessEvents()
{
    for(auto&& task : m_RenderCommands)
    {
        m_TaskGroup.run(std::move(task));
    }
    m_RenderCommands.clear();
}
