#include "RenderSystem.h"


RenderSystem::RenderSystem(std::shared_ptr<Entity> mainCameraEntity)
    : m_mainCameraEntity(mainCameraEntity) {}

bool RenderSystem::getRenderContext(RenderContext& context) const {
    if (!m_mainCameraEntity) return false;
    auto camera = m_mainCameraEntity->getComponent<CameraComponent>();
    if (!camera) return false;

    context.view = camera->getViewMatrix();
    context.projection = camera->getProjectionMatrix();
    context.viewPos = camera->getPosition();
    return true;
}

void RenderSystem::renderEntity(const std::shared_ptr<Entity>& entity, const RenderContext& context) {
    auto transform = entity->getComponent<TransformComponent>();
    auto mesh = entity->getComponent<MeshComponent>();
    auto material = entity->getComponent<MaterialComponent>();

    if (!transform || !mesh || !material) return;

    auto shader = material->getShader();
    if (!shader) return;

    shader->use();
    
    // 设置全局矩阵和参数
    shader->setMat4("view", context.view);
    shader->setMat4("projection", context.projection);
    shader->setVec3("viewPos", context.viewPos);
    shader->setMat4("model", transform->getModelMatrix());

    // 设置材质属性
    shader->setBool("useTexture", material->getUseTexture());
    shader->setBool("useLighting", material->getUseLighting());
    shader->setVec3("overrideColor", material->getOverrideColor());

    // 设置默认材质和光照参数
    static const struct {
        glm::vec3 ambient{1.0f, 0.5f, 0.31f};
        glm::vec3 diffuse{1.0f, 0.5f, 0.31f};
        glm::vec3 specular{0.5f, 0.5f, 0.5f};
        float shininess{32.0f};
        glm::vec3 lightPos{1.2f, 1.0f, 2.0f};
        glm::vec3 lightAmbient{0.2f};
        glm::vec3 lightDiffuse{0.5f};
        glm::vec3 lightSpecular{1.0f};
    } defaults;

    shader->setVec3("material.ambient", defaults.ambient);
    shader->setVec3("material.diffuse", defaults.diffuse);
    shader->setVec3("material.specular", defaults.specular);
    shader->setFloat("material.shininess", defaults.shininess);
    shader->setVec3("light.position", defaults.lightPos);
    shader->setVec3("light.ambient", defaults.lightAmbient);
    shader->setVec3("light.diffuse", defaults.lightDiffuse);
    shader->setVec3("light.specular", defaults.lightSpecular);

    // 绑定纹理
    if (material->getUseTexture()) {
        if (auto texture = material->getTexture()) {
            texture->bind();
        }
    }

    // 设置绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, material->getWireframeMode() ? GL_LINE : GL_FILL);

    // 绘制
    mesh->bind();
    glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
}

void RenderSystem::update(float deltaTime) {
    RenderContext context;
    if (!getRenderContext(context)) return;

    for (const auto& entity : m_entities) {
        renderEntity(entity, context);
    }
}