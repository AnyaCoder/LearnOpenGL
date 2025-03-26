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

    void setCursorCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(m_Window, callback);
    }

    void setUserPointer(void* pointer) {
        glfwSetWindowUserPointer(m_Window, pointer);
    }

    void setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
        glfwSetFramebufferSizeCallback(m_Window, callback);
    }

    void getSize(int* width, int* height) {
        glfwGetFramebufferSize(m_Window, width, height);
    }

private:
    GLFWwindow* m_Window;
};
