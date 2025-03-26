#include "Application.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"
#include "InputHandler.h"

Application::Application() {
    initialize();
}

Application::~Application() {}

void Application::initialize() {
    m_window = std::make_unique<Window>(1600, 900, "LearnOpenGL");
    m_shader = std::make_unique<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");
    m_texture = std::make_unique<Texture>("resources/texture.png");
    m_camera = std::make_unique<Camera>();
    m_renderer = std::make_unique<Renderer>(m_window.get(), m_shader.get(), m_texture.get());
    m_scene = std::make_unique<Scene>();
    m_inputHandler = std::make_unique<InputHandler>(m_window->getNativeWindow(), m_camera.get(), m_renderer.get());

    m_window->setUserPointer(this);
    m_window->setCursorCallback([](GLFWwindow* window, double xpos, double ypos) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->m_camera->processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    });
    m_window->setFramebufferSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

void Application::run() {
    while (!m_window->shouldClose()) {
        m_inputHandler->processInput();

        int width, height;
        m_window->getSize(&width, &height);
        glm::mat4 projection = glm::perspective(glm::radians(m_camera->getFov()), (float)width / (float)height, 0.1f, 100.0f);
        m_renderer->render(m_scene->getMeshes(), m_camera->getViewMatrix(), projection, m_camera->getPosition());

        m_window->swapBuffers();
        m_window->pollEvents();
    }
}