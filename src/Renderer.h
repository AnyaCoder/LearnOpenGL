#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

class Renderer {
public:
    Renderer(Window* window, Shader* shader, Texture* texture);
    void render(const std::vector<std::unique_ptr<Mesh>>& meshes, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos);

    void setUseTexture(bool use) { m_useTexture = use; }
    bool getUseTexture() { return m_useTexture; }
    void setWireframeMode(bool mode) { m_wireframeMode = mode; }
    bool getWireframeMode() { return m_wireframeMode; }
    void setUseLighting(bool use) { m_useLighting = use; }
    bool getUseLighting() { return m_useLighting; }
    void setOverrideColor(const glm::vec3& color) { m_overrideColor = color; }
    void setLightPos(const glm::vec3& pos) { m_lightPos = pos; }

private:
    Window* m_window;
    Shader* m_shader;
    Texture* m_texture;
    glm::vec3 m_lightPos;
    glm::vec3 m_overrideColor;
    bool m_useTexture;
    bool m_wireframeMode;
    bool m_useLighting;
};

#endif
