#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(Window* window, Shader* shader, Texture* texture)
    : m_window(window), m_shader(shader), m_texture(texture),
      m_lightPos(1.2f, 1.0f, 2.0f), m_overrideColor(1.0f),
      m_useTexture(true), m_wireframeMode(false), m_useLighting(true) {}

void Renderer::render(const std::vector<std::unique_ptr<Mesh>>& meshes, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) {
    m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);
    m_shader->use();

    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);

    m_shader->setBool("useLighting", m_useLighting);
    if (m_useLighting) {
        m_shader->setVec3("viewPos", cameraPos);
        m_shader->setVec3("light.position", m_lightPos);
        m_shader->setVec3("light.ambient", glm::vec3(0.2f));
        m_shader->setVec3("light.diffuse", glm::vec3(0.5f));
        m_shader->setVec3("light.specular", glm::vec3(1.0f));
        m_shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        m_shader->setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        m_shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        m_shader->setFloat("material.shininess", 32.0f);
    }
    m_shader->setBool("useTexture", m_useTexture);
    m_shader->setVec3("overrideColor", m_overrideColor);

    if (m_useTexture)
        m_texture->bind();

    glPolygonMode(GL_FRONT_AND_BACK, m_wireframeMode ? GL_LINE : GL_FILL);

    glLineWidth(3.0f);
    for (int i = 0; i < 3; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        m_shader->setMat4("model", model);
        meshes[i]->draw();
    }
    glLineWidth(1.0f);

    for (int x = -1; x <= 1; x++) {
        for (int z = -1; z <= 1; z++) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x * 1.2f, 0.0f, z * 1.2f));
            m_shader->setMat4("model", model);
            meshes[3]->draw();
        }
    }
}