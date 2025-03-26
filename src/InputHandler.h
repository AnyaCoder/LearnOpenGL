#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <glm/glm.hpp>
#include "Camera.h"
#include "Renderer.h"


class InputHandler {
public:
    InputHandler(GLFWwindow* window, Camera* camera, Renderer* renderer);
    void processInput();

private:
    GLFWwindow* m_window;
    Camera* m_camera;
    Renderer* m_renderer;
};

#endif