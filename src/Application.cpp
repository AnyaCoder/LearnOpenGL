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
    
    // Initialize camera
    m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw = -90.0f;
    m_pitch = 0.0f;
    m_lastX = 400.0f;
    m_lastY = 300.0f;
    m_firstMouse = true;
    m_fov = 45.0f;
    
    // Initialize lighting
    m_lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    m_viewPos = m_cameraPos;
}

void Application::initializeWindow() {
    m_Window = std::make_unique<Window>(800, 600, "LearnOpenGL");
    m_Window->setUserPointer(this);
    m_Window->setCursorCallback(mouseCallback);
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
        Vertex(glm::vec3(0.0f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f))
    };
    std::vector<unsigned int> indices1 = {0, 1, 2};
    m_meshes.push_back(std::make_unique<Mesh>(triangle1, indices1));

    // 三角形2: 等腰直角三角形
    std::vector<Vertex> triangle2 = {
        Vertex(glm::vec3(0.0f,  0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f,  0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.0f,  1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f))
    };
    m_meshes.push_back(std::make_unique<Mesh>(triangle2, indices1));

    // 三角形3: 细长三角形
    std::vector<Vertex> triangle3 = {
        Vertex(glm::vec3(0.0f,  0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3(0.8f, -0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.8f, -0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
    };
    m_meshes.push_back(std::make_unique<Mesh>(triangle3, indices1));
}

void Application::processInput() {
    float cameraSpeed = 0.05f;
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_Window->getNativeWindow(), true);
    }
    
    // 相机移动
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        m_cameraPos += cameraSpeed * m_cameraFront;
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        m_cameraPos -= cameraSpeed * m_cameraFront;
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(m_Window->getNativeWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
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
    
    // 设置变换矩阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(m_fov), 800.0f / 600.0f, 0.1f, 100.0f);
    
    m_Shader->setMat4("model", model);
    m_Shader->setMat4("view", view);
    m_Shader->setMat4("projection", projection);
    
    // 设置光照uniforms
    m_Shader->setVec3("viewPos", m_cameraPos);
    m_Shader->setVec3("light.position", m_lightPos);
    m_Shader->setVec3("light.ambient", glm::vec3(0.2f));
    m_Shader->setVec3("light.diffuse", glm::vec3(0.5f));
    m_Shader->setVec3("light.specular", glm::vec3(1.0f));
    
    // 设置材质uniforms
    m_Shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_Shader->setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_Shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->setFloat("material.shininess", 32.0f);
    
    m_Shader->setBool("useTexture", m_useTexture);
    m_Shader->setVec3("overrideColor", m_overrideColor);
    
    if (m_useTexture) {
        m_Texture->bind();
    }
    
    m_meshes[m_currentShape]->draw();
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    }
}

void Application::processMouseMovement(float xpos, float ypos) {
    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // 反转y坐标
    m_lastX = xpos;
    m_lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // 限制俯仰角
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // 计算新的前向量
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
}

void Application::cleanup() {
}
