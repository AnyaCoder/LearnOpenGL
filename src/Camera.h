#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    void processMouseMovement(float xpos, float ypos);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const { return m_cameraPos; }
    glm::vec3 getFront() const { return m_cameraFront; }
    void setPosition(const glm::vec3& pos) { m_cameraPos = pos; }
    void setFov(float fov) { m_fov = fov; }
    float getFov() const { return m_fov; }

private:
    glm::vec3 m_cameraPos, m_cameraFront, m_cameraUp;
    float m_yaw, m_pitch, m_lastX, m_lastY, m_fov;
    bool m_firstMouse;
};

#endif