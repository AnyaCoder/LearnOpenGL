#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow* window, std::shared_ptr<CameraComponent> camera, std::shared_ptr<RenderSystem> renderSystem)
    : m_window(window), m_camera(camera), m_renderSystem(renderSystem)
{
        
    // 验证输入
    if (!m_window || !m_camera || !m_renderSystem) {
        m_isValid = false;
        return;
    }
    m_lastPressTime = (double)0.0f;
    m_isValid = true;

    // 初始化相机移动映射
    m_movementKeys = {
        {GLFW_KEY_W, [this]() { return m_camera->getFront() * CAMERA_SPEED; }},
        {GLFW_KEY_S, [this]() { return -m_camera->getFront() * CAMERA_SPEED; }},
        {GLFW_KEY_D, [this]() { return glm::normalize(glm::cross(m_camera->getFront(), m_camera->getUp())) * CAMERA_SPEED; }},
        {GLFW_KEY_A, [this]() { return -glm::normalize(glm::cross(m_camera->getFront(), m_camera->getUp())) * CAMERA_SPEED; }}
    };

    // 初始化模式切换映射
    m_modeKeys = {
        {GLFW_KEY_T, [](std::shared_ptr<MaterialComponent> m) { m->setUseTexture(!m->getUseTexture()); }},
        {GLFW_KEY_F, [](std::shared_ptr<MaterialComponent> m) { m->setWireframeMode(!m->getWireframeMode()); }},
        {GLFW_KEY_L, [](std::shared_ptr<MaterialComponent> m) { m->setUseLighting(!m->getUseLighting()); }}
    };

    // 初始化颜色切换映射
    m_colorKeys = {
        {GLFW_KEY_R, glm::vec3(1.0f, 0.0f, 0.0f)},
        {GLFW_KEY_G, glm::vec3(0.0f, 1.0f, 0.0f)},
        {GLFW_KEY_B, glm::vec3(0.0f, 0.0f, 1.0f)}
    };
}

void InputHandler::processInput() {
    if (!m_isValid) return;

    double currentTime = glfwGetTime();

    // 退出程序
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
        return;
    }

    // 相机移动
    glm::vec3 pos = m_camera->getPosition();
    for (const auto& [key, getOffset] : m_movementKeys) {
        if (glfwGetKey(m_window, key) == GLFW_PRESS) {
            pos += getOffset();
        }
    }
    m_camera->setPosition(pos);

    // 处理模式和颜色切换
    auto processToggle = [&](int key, const auto& action) {
        if (glfwGetKey(m_window, key) == GLFW_PRESS && currentTime - m_lastPressTime > DEBOUNCE_TIME) {
            m_renderSystem->forEachEntity([&](std::shared_ptr<Entity> entity) {
                if (auto material = entity->getComponent<MaterialComponent>()) {
                    action(material);
                }
            });
            m_lastPressTime = currentTime;
        }
    };

    for (const auto& [key, func] : m_modeKeys) {
        processToggle(key, func);
    }
    
    for (const auto& [key, color] : m_colorKeys) {
        processToggle(key, [color](std::shared_ptr<MaterialComponent> m) { m->setOverrideColor(color); });
    }
}
