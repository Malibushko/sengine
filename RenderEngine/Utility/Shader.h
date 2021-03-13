#pragma  once
#include <string_view>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader( std::string_view vertex, std::string_view fragment );
    ~Shader();

    void Use() const;

    unsigned int GetId() const;

    void Set( std::string_view name, bool value ) const;
    void Set( std::string_view name, int value ) const;
    void Set( std::string_view name, float value ) const;
    void Set( std::string_view name, double value ) const;
    void Set( std::string_view name, const glm::mat4& mat ) const;
    void Set( std::string_view name, const glm::vec3& vec ) const;
    void Set( std::string_view name, float x, float y, float z ) const;
private:
    using vertex_t = unsigned int;
    unsigned int m_ID = -1;

    vertex_t m_VertexShader = -1;
    vertex_t m_FragmentShader = -1;
};
