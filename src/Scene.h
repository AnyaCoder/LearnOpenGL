// Scene.h
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Mesh.h"

class Scene {
public:
    Scene();
    const std::vector<std::unique_ptr<Mesh>>& getMeshes() const { return m_meshes; }

private:
    void createCoordinateAxes();
    void createCubeMesh();
    std::vector<std::unique_ptr<Mesh>> m_meshes;
};

#endif
