#pragma once
#include "Component.h"
#include "../Vertex.h"
#include <vector>
#include <glad/glad.h>

class MeshComponent : public Component {
public:
    MeshComponent(const std::vector<Vertex>& vertices,
                const std::vector<unsigned int>& indices);
    ~MeshComponent();

    void setupBuffers();
    void bind() const;

    GLsizei getIndexCount() const { return m_indexCount; }

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLsizei m_indexCount;
};
