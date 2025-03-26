#include "InputHandler.h"
#include "Camera.h"
#include "Renderer.h"

InputHandler::InputHandler(GLFWwindow* window, Camera* camera, Renderer* renderer)
    : m_window(window), m_camera(camera), m_renderer(renderer) {}

void InputHandler::processInput() {
    static double lastPressTime = 0.0; // 用于防抖
    double currentTime = glfwGetTime();
    float cameraSpeed = 0.05f;

    // 退出程序
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }

    // 相机移动
    glm::vec3 pos = m_camera->getPosition();
    glm::vec3 front = m_camera->getFront(); // 假设 Camera 提供 getFront() 获取朝向
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // 假设固定向上向量

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        pos += cameraSpeed * front; // 前进
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        pos -= cameraSpeed * front; // 后退
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed; // 左移
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
        pos += glm::normalize(glm::cross(front, up)) * cameraSpeed; // 右移
    }
    m_camera->setPosition(pos); // 更新相机位置

    // 切换模式（添加防抖，避免连续触发）
    if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setUseTexture(!m_renderer->getUseTexture());
        lastPressTime = currentTime;
    }
    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setWireframeMode(!m_renderer->getWireframeMode());
        lastPressTime = currentTime;
    }
    if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setUseLighting(!m_renderer->getUseLighting());
        lastPressTime = currentTime;
    }

    // 改变颜色（同样添加防抖）
    if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setOverrideColor(glm::vec3(1.0f, 0.0f, 0.0f)); // 红色
        lastPressTime = currentTime;
    }
    if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setOverrideColor(glm::vec3(0.0f, 1.0f, 0.0f)); // 绿色
        lastPressTime = currentTime;
    }
    if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS && currentTime - lastPressTime > 0.2) {
        m_renderer->setOverrideColor(glm::vec3(0.0f, 0.0f, 1.0f)); // 蓝色
        lastPressTime = currentTime;
    }
}