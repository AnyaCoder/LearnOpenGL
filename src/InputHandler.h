#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <glm/glm.hpp>
#include "ECS/Entity.h"
#include "ECS/RenderSystem.h"
#include "ECS/CameraComponent.h"
#include "ECS/MaterialComponent.h"
#include "Core.h"

class InputHandler {
public:
    InputHandler(GLFWwindow* window, std::shared_ptr<CameraComponent> camera, std::shared_ptr<RenderSystem> renderSystem);
    void processInput();

private:
    static constexpr float CAMERA_SPEED = 0.05f;
    static constexpr float DEBOUNCE_TIME = 0.2f;

    GLFWwindow* m_window;
    std::shared_ptr<RenderSystem> m_renderSystem;
    std::shared_ptr<CameraComponent> m_camera;  // 缓存相机组件指针
    double m_lastPressTime;
    bool m_isValid = true;

    // 按键映射表
    std::unordered_map<int, std::function<glm::vec3()>> m_movementKeys;
    std::unordered_map<int, std::function<void(std::shared_ptr<MaterialComponent>)>> m_modeKeys;
    std::unordered_map<int, glm::vec3> m_colorKeys;
};

#endif
