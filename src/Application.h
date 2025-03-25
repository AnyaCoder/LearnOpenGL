#pragma once

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
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
    unsigned int m_VAO, m_VBO, m_EBO;
};
