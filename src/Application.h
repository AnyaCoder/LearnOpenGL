#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "ECS/ECSManager.h"
#include "ECS/RenderSystem.h"
#include "InputHandler.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    void initialize();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<ECSManager> m_ecs;
    std::shared_ptr<Entity> m_rendererEntity;
    std::shared_ptr<Entity> m_cameraEntity;
    std::unique_ptr<InputHandler> m_inputHandler;
};

#endif
