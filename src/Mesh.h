#pragma once
#include "Vertex.h"
#include <vector>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    
    void draw() const;
    
private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};
