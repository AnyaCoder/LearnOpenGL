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
    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    m_Mesh = std::make_unique<Mesh>(vertices, indices);
}

void Application::processInput() {
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_Window->getNativeWindow(), true);
    }
}

void Application::render() {
    m_Window->clear(0.2f, 0.3f, 0.3f, 1.0f);
    
    m_Texture->bind();
    m_Shader->use();
    
    m_Mesh->draw();
}

void Application::cleanup() {
}
