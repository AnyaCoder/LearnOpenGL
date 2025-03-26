#include "Application.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Mesh.h"

Application::Application() {
    initialize();
}

Application::~Application() {
    cleanup();
}

void Application::run() {
    while (!m_Window->shouldClose()) {
        processInput();
        render();
        m_Window->swapBuffers();
        m_Window->pollEvents();
    }
}

void Application::initialize() {
    initializeWindow();
    initializeShaders();
    initializeTextures();
    initializeRenderData();
}

void Application::initializeWindow() {
    m_Window = std::make_unique<Window>(800, 600, "LearnOpenGL");
}

void Application::initializeShaders() {
    m_Shader = std::make_unique<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");
}

void Application::initializeTextures() {
    m_Texture = std::make_unique<Texture>("resources/texture.png");
}

void Application::initializeRenderData() {
    // 创建不同形状的三角形
    createTriangleMeshes();
    m_currentShape = 0;
    m_useTexture = true;
    m_overrideColor = glm::vec3(1.0f);
}

void Application::createTriangleMeshes() {
    // 三角形1: 普通三角形
    std::vector<Vertex> triangle1 = {
        Vertex(glm::vec3(0.0f,  0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f))
    };
    std::vector<unsigned int> indices1 = {0, 1, 2};
    m_meshes.push_back(std::make_unique<Mesh>(triangle1, indices1));

    // 三角形2: 等腰直角三角形
    std::vector<Vertex> triangle2 = {
        Vertex(glm::vec3(0.0f,  0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f,  0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.0f,  1.0f, 0.0f), glm::vec3(0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f))
    };
    m_meshes.push_back(std::make_unique<Mesh>(triangle2, indices1));

    // 三角形3: 细长三角形
    std::vector<Vertex> triangle3 = {
        Vertex(glm::vec3(0.0f,  0.3f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3(0.8f, -0.3f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.8f, -0.3f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
    };
    m_meshes.push_back(std::make_unique<Mesh>(triangle3, indices1));
}

void Application::processInput() {
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_Window->getNativeWindow(), true);
    }
    
    // 切换形状
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_1) == GLFW_PRESS) {
        m_currentShape = 0;
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_2) == GLFW_PRESS) {
        m_currentShape = 1;
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_3) == GLFW_PRESS) {
        m_currentShape = 2;
    }
    
    // 切换纹理/颜色模式
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_T) == GLFW_PRESS) {
        m_useTexture = !m_useTexture;
    }
    
    // 改变颜色
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_R) == GLFW_PRESS) {
        m_overrideColor = glm::vec3(1.0f, 0.0f, 0.0f); // 红色
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_G) == GLFW_PRESS) {
        m_overrideColor = glm::vec3(0.0f, 1.0f, 0.0f); // 绿色
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_B) == GLFW_PRESS) {
        m_overrideColor = glm::vec3(0.0f, 0.0f, 1.0f); // 蓝色
    }
}

void Application::render() {
    m_Window->clear(0.2f, 0.3f, 0.3f, 1.0f);
    
    m_Shader->use();
    m_Shader->setBool("useTexture", m_useTexture);
    m_Shader->setVec3("overrideColor", m_overrideColor);
    
    if (m_useTexture) {
        m_Texture->bind();
    }
    
    m_meshes[m_currentShape]->draw();
}

void Application::cleanup() {
}
