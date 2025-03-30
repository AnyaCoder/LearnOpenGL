#pragma once
#include <memory>
#include "Component.h"
#include "../Shader.h"
#include "../Texture.h"
#include <glm/glm.hpp>

class MaterialComponent : public Component {
public:
    MaterialComponent(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture = nullptr)
        : m_shader(shader), m_texture(texture),
          m_useTexture(true), m_wireframeMode(false),
          m_useLighting(true), m_overrideColor(1.0f) {}

    std::shared_ptr<Shader> getShader() const { return m_shader; }
    std::shared_ptr<Texture> getTexture() const { return m_texture; }
    void setTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }

    bool getUseTexture() const { return m_useTexture; }
    void setUseTexture(bool use) { m_useTexture = use; }

    bool getWireframeMode() const { return m_wireframeMode; }
    void setWireframeMode(bool wireframe) { m_wireframeMode = wireframe; }

    bool getUseLighting() const { return m_useLighting; }
    void setUseLighting(bool use) { m_useLighting = use; }

    glm::vec3 getOverrideColor() const { return m_overrideColor; }
    void setOverrideColor(const glm::vec3& color) { m_overrideColor = color; }

private:
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture> m_texture;
    bool m_useTexture;
    bool m_wireframeMode;
    bool m_useLighting;
    glm::vec3 m_overrideColor;
};