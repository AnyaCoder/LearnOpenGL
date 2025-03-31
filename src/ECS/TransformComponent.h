#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformComponent : public Component {
public:
    TransformComponent() = default;
    TransformComponent(const glm::vec3& position) 
        : position(position) {}
    
    // 获取模型矩阵 - 使用正确的变换顺序：缩放 -> 旋转 -> 平移
    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        // 先缩放
        model = glm::scale(model, scale);
        // 然后旋转（X、Y、Z顺序）
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        // 最后平移
        model = glm::translate(model, position);
        return model;
    }

    // 获取各个变换的单独矩阵
    glm::mat4 getTranslationMatrix() const { return glm::translate(glm::mat4(1.0f), position); }
    glm::mat4 getRotationMatrix() const {
        glm::mat4 rot = glm::mat4(1.0f);
        rot = glm::rotate(rot, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rot = glm::rotate(rot, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rot = glm::rotate(rot, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        return rot;
    }
    glm::mat4 getScaleMatrix() const { return glm::scale(glm::mat4(1.0f), scale); }

    // 设置函数
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    void setScale(const glm::vec3& scl) { scale = scl; }
    void setScale(float uniformScale) { scale = glm::vec3(uniformScale); }

    // 增量修改函数
    void translate(const glm::vec3& offset) { position += offset; }
    void rotate(const glm::vec3& rot) { rotation += rot; }
    void scaleBy(const glm::vec3& scl) { scale *= scl; }

    // 获取物体的前向向量（世界坐标）
    glm::vec3 getForward() const {
        glm::mat4 rotMat = getRotationMatrix();
        return glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    }

    // 获取右向量（世界坐标）
    glm::vec3 getRight() const {
        glm::mat4 rotMat = getRotationMatrix();
        return glm::normalize(glm::vec3(rotMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
    }

    // 获取上向量（世界坐标）
    glm::vec3 getUp() const {
        glm::mat4 rotMat = getRotationMatrix();
        return glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
    }

public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);  // 欧拉角（度）
    glm::vec3 scale = glm::vec3(1.0f);
};