#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraComponent : public Component {
public:
    CameraComponent(float fov = 45.0f, float near = 0.1f, float far = 100.0f);

    void updateViewMatrix();
    void updateProjectionMatrix(int width, int height);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    glm::mat4 getViewMatrix() const { return m_viewMatrix; }
    glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getFront() const { return m_front; }
    glm::vec3 getUp() const { return m_up; }
    float getFov() const { return m_fov; }

    void setPosition(const glm::vec3& position) { 
        m_position = position;
        updateViewMatrix();
    }

private:
    void updateCameraVectors();

    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_mouseSensitivity = 0.1f;
    
    float m_fov;
    float m_near;
    float m_far;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};
