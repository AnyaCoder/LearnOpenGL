#include "Camera.h"

Camera::Camera() {
    m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);    // 初始位置
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // 初始朝向
    m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // 上方向
    m_yaw = -90.0f;                               // 初始偏航角
    m_pitch = 0.0f;                               // 初始俯仰角
    m_lastX = 400.0f;                             // 初始鼠标 X 位置
    m_lastY = 300.0f;                             // 初始鼠标 Y 位置
    m_firstMouse = true;                          // 首次鼠标输入标志
    m_fov = 45.0f;                                // 初始视野角度
}

void Camera::processMouseMovement(float xpos, float ypos) {
    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // Y 轴反转
    m_lastX = xpos;
    m_lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // 限制俯仰角，避免翻转
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;

    // 更新相机朝向
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}