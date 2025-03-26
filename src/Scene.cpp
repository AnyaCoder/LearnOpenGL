#include "Scene.h"
#include "Mesh.h"
#include "Vertex.h"

Scene::Scene() {
    createCoordinateAxes();
    createCubeMesh();
}

void Scene::createCoordinateAxes() {
    std::vector<Vertex> xAxis = {
        Vertex(glm::vec3(-100.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)),
        Vertex(glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f))
    };
    std::vector<unsigned int> xIndices = {0, 1};
    m_meshes.push_back(std::make_unique<Mesh>(xAxis, xIndices));
    m_meshes.back()->setDrawMode(GL_LINES);

    std::vector<Vertex> yAxis = {
        Vertex(glm::vec3(0.0f, -100.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)),
        Vertex(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f))
    };
    std::vector<unsigned int> yIndices = {0, 1};
    m_meshes.push_back(std::make_unique<Mesh>(yAxis, yIndices));
    m_meshes.back()->setDrawMode(GL_LINES);

    std::vector<Vertex> zAxis = {
        Vertex(glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f)),
        Vertex(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f))
    };
    std::vector<unsigned int> zIndices = {0, 1};
    m_meshes.push_back(std::make_unique<Mesh>(zAxis, zIndices));
    m_meshes.back()->setDrawMode(GL_LINES);
}

void Scene::createCubeMesh() {
    std::vector<Vertex> vertices = {
        // 前 (Z = 0.5)
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 2
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 3
    
        // 后 (Z = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 4
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 5
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 6
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 7
    
        // 左 (X = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 8
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 9
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 10
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 11
    
        // 右 (X = 0.5)
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 12
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 13
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 14
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 15
    
        // 上 (Y = 0.5)
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 16
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 17
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 18
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 19
    
        // 下 (Y = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 20
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 21
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 22
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 23
    };
    
    // 要判断为正面，三角面的顶点定义必须为逆时针方向
    std::vector<unsigned int> indices = {
        // 前
        0, 1, 2,  0, 2, 3,
        // 后
        4, 5, 6,  4, 6, 7,
        // 左
        8, 10, 9,  8, 11, 10,
        // 右
        12, 14, 13,  12, 15, 14,
        // 上
        16, 17, 18,  16, 18, 19,
        // 下
        20, 21, 22,  20, 22, 23
    };

    m_meshes.push_back(std::make_unique<Mesh>(vertices, indices));
}