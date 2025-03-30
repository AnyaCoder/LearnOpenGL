#include "CameraComponent.h"

CameraComponent::CameraComponent(float fov, float near, float far)
    : m_fov(fov), m_near(near), m_far(far) {
    updateCameraVectors();
}

void CameraComponent::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
}

void CameraComponent::updateProjectionMatrix(int width, int height) {
    m_projectionMatrix = glm::perspective(
        glm::radians(m_fov),
        static_cast<float>(width) / static_cast<float>(height),
        m_near,
        m_far
    );
}

void CameraComponent::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;
    }

    updateCameraVectors();
}

void CameraComponent::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    updateViewMatrix();
}
