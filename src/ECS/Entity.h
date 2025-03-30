#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>
#include "Component.h"

class Entity {
public:
    template<typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[std::type_index(typeid(T))] = component;
        return component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent() {
        auto it = m_components.find(std::type_index(typeid(T)));
        if (it != m_components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    void removeComponent() {
        m_components.erase(std::type_index(typeid(T)));
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};