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
        Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f))
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,  0, 2, 3,  // front
        4, 6, 5,  4, 7, 6,  // back
        4, 0, 3,  4, 3, 7,  // left
        1, 5, 6,  1, 6, 2,  // right
        3, 2, 6,  3, 6, 7,  // up
        4, 5, 1,  4, 1, 0   // down
    };

    m_meshes.push_back(std::make_unique<Mesh>(vertices, indices));
}