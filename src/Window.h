#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void clear(float r, float g, float b, float a);

    GLFWwindow* getNativeWindow() const { return m_Window; }

private:
    GLFWwindow* m_Window;
};
