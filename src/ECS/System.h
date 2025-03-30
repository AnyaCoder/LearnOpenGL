#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class System {
public:
    virtual ~System() = default;
    virtual void update(float deltaTime) = 0;

    void registerEntity(std::shared_ptr<Entity> entity) {
        m_entities.push_back(entity);
    }

    void unregisterEntity(std::shared_ptr<Entity> entity) {
        m_entities.erase(
            std::remove(m_entities.begin(), m_entities.end(), entity),
            m_entities.end()
        );
    }

    template<typename Func>
    void forEachEntity(Func&& func) {
        for (auto& entity : m_entities) {
            func(entity);
        }
    }

protected:
    std::vector<std::shared_ptr<Entity>> m_entities;
};