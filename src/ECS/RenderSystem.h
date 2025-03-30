#pragma once
#include "System.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "CameraComponent.h"

class RenderSystem : public System {
public:
    RenderSystem(std::shared_ptr<Entity> mainCameraEntity);
    void update(float deltaTime) override;

private:
    struct RenderContext {
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 viewPos;
    };

    bool getRenderContext(RenderContext& context) const;
    void renderEntity(const std::shared_ptr<Entity>& entity, const RenderContext& context);

    std::shared_ptr<Entity> m_mainCameraEntity;
};