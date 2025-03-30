#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "System.h"

class ECSManager {
public:
    std::shared_ptr<Entity> createEntity() {
        auto entity = std::make_shared<Entity>();
        m_entities.push_back(entity);
        return entity;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> addSystem(Args&&... args) {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        m_systems.push_back(system);
        return system;
    }

    void update(float deltaTime) {
        for (auto& system : m_systems) {
            system->update(deltaTime);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<System>> m_systems;
};