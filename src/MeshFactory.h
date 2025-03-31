#pragma once
#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

class MeshFactory {
public:
    // 生成立方体的顶点和索引
    static void createCube(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    // 生成圆柱体的顶点和索引
    static void createCylinder(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                             float radius = 0.5f, float height = 1.0f, int segments = 32);
    // 生成球体的顶点和索引
    static void createSphere(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                           float radius = 0.5f, int sectors = 32, int stacks = 16);
    
    // 生成胶囊体的顶点和索引
    static void createCapsule(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
        float radius = 0.5f, float height = 1.0f, int segments = 32, int capStacks = 8);

    // 生成锥体的顶点和索引
    static void createCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                            float radius = 0.5f, float height = 1.0f, int segments = 32);
};