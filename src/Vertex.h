#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texCoord;
    
    Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec3& col, const glm::vec2& tex)
        : position(pos), normal(norm), color(col), texCoord(tex) {}
};
