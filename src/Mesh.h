#pragma once
#include "Vertex.h"
#include <vector>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void setupMesh();
    ~Mesh();
    
    void draw() const;
    void setDrawMode(GLenum mode) { m_drawMode = mode; }
    
private:
    GLenum m_drawMode = GL_TRIANGLES;
    
private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLsizei m_indexCount;
};
