#pragma once

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    void initialize();
    void initializeWindow();
    void initializeShaders();
    void initializeTextures();
    void initializeRenderData();
    void processInput();
    void render();
    void cleanup();

    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    
    // Render data
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    std::unique_ptr<Mesh> m_Mesh;
    int m_currentShape;
    bool m_useTexture;
    glm::vec3 m_overrideColor;
    
    // Camera
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    float m_yaw;
    float m_pitch;
    float m_lastX;
    float m_lastY;
    bool m_firstMouse;
    float m_fov;
    
    // Lighting
    glm::vec3 m_lightPos;
    glm::vec3 m_viewPos;
    
    void createTriangleMeshes();
    void switchShape();
    void toggleTexture();
    void changeColor();
    
    // 鼠标回调
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void processMouseMovement(float xoffset, float yoffset);
};
