#pragma once

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include <memory>

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
    
    void createTriangleMeshes();
    void switchShape();
    void toggleTexture();
    void changeColor();
};
