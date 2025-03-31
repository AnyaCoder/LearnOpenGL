#include "MeshFactory.h"


// 生成立方体的顶点和索引
void MeshFactory::createCube(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    vertices = {
        // 前 (Z = 0.5)
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 2
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 3
    
        // 后 (Z = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 4
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 5
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 6
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 7
    
        // 左 (X = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 8
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 9
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 10
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 11
    
        // 右 (X = 0.5)
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 12
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 13
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 14
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 15
    
        // 上 (Y = 0.5)
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 16
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 17
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 18
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 19
    
        // 下 (Y = -0.5)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 20
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 21
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 22
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 23
    };
    
    // 要判断为正面，三角面的顶点定义必须为逆时针方向
    indices = {
        // 前
        0, 1, 2,  0, 2, 3,
        // 后
        4, 5, 6,  4, 6, 7,
        // 左
        8, 10, 9,  8, 11, 10,
        // 右
        12, 14, 13,  12, 15, 14,
        // 上
        16, 17, 18,  16, 18, 19,
        // 下
        20, 21, 22,  20, 22, 23
    };
}

// 生成圆柱体的顶点和索引
void MeshFactory::createCylinder(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                            float radius, float height, int segments) {
    vertices.clear();
    indices.clear();

    // 顶面和底面中心
    vertices.push_back({{0.0f, height / 2, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}}); // 顶中心
    vertices.push_back({{0.0f, -height / 2, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}}); // 底中心

    // 生成侧面顶点
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * glm::pi<float>() * i / segments;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        
        // 顶面顶点
        vertices.push_back({{x, height / 2, z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {cosf(angle) * 0.5f + 0.5f, sinf(angle) * 0.5f + 0.5f}});
        // 底面顶点
        vertices.push_back({{x, -height / 2, z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {cosf(angle) * 0.5f + 0.5f, sinf(angle) * 0.5f + 0.5f}});
        // 侧面法线
        glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));
        vertices.push_back({{x, height / 2, z}, normal, {1.0f, 1.0f, 1.0f}, {float(i) / segments, 1.0f}});
        vertices.push_back({{x, -height / 2, z}, normal, {1.0f, 1.0f, 1.0f}, {float(i) / segments, 0.0f}});
    }

    // 顶面索引
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        indices.push_back(0);                   // 顶中心
        indices.push_back(2 + next * 4);        // 下一个顶面顶点
        indices.push_back(2 + i * 4);           // 当前顶面顶点
    }

    // 底面索引
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        indices.push_back(1);                   // 底中心
        indices.push_back(3 + i * 4);           // 当前底面顶点
        indices.push_back(3 + next * 4);        // 下一个底面顶点
    }

    // 侧面索引
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        // 第一个三角形
        indices.push_back(4 + i * 4);      // 当前顶
        indices.push_back(4 + next * 4);   // 下一个顶
        indices.push_back(5 + i * 4);      // 当前底
        // 第二个三角形
        indices.push_back(4 + next * 4);   // 下一个顶
        indices.push_back(5 + next * 4);   // 下一个底
        indices.push_back(5 + i * 4);      // 当前底
    }
}

// 生成球体的顶点和索引
void MeshFactory::createSphere(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                        float radius, int sectors, int stacks) {
    vertices.clear();
    indices.clear();

    for (int i = 0; i <= stacks; ++i) {
        float v = i / (float)stacks;
        float phi = v * glm::pi<float>();
        for (int j = 0; j <= sectors; ++j) {
            float u = j / (float)sectors;
            float theta = u * 2.0f * glm::pi<float>();

            float x = radius * cosf(theta) * sinf(phi);
            float y = radius * cosf(phi);
            float z = radius * sinf(theta) * sinf(phi);

            glm::vec3 pos(x, y, z);
            glm::vec3 normal = glm::normalize(pos);
            vertices.push_back({pos, normal, {1.0f, 1.0f, 1.0f}, {u, v}});
        }
    }

    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < sectors; ++j) {
            int a = i * (sectors + 1) + j;
            int b = a + 1;
            int c = (i + 1) * (sectors + 1) + j;
            int d = c + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(c);
        }
    }
}

// 生成胶囊体
/*
胶囊体 (Capsule)
    结构：由上半球、下半球和中间的圆柱连接部分组成。

    参数：
        radius：半球和圆柱的半径。

        height：中间圆柱部分的长度（不包括半球）。

        segments：圆周分段数。

        capStacks：半球的垂直分段数。

    实现：分为三个部分生成顶点（上半球、下半球、圆柱侧面），分别计算索引以连接这些部分。

    法线：上半球和下半球的法线相对于各自球心，圆柱侧面法线为径向。
*/
void MeshFactory::createCapsule(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                        float radius, float height, int segments, int capStacks) {
    vertices.clear();
    indices.clear();

    float halfHeight = height / 2.0f;

    // 上半球部分（从 y = 0 到 y = halfHeight）
    for (int i = 0; i <= capStacks; ++i) {
        float v = i / (float)capStacks * 0.5f;  // 只生成上半球，phi 从 0 到 pi/2
        float phi = v * glm::pi<float>();
        for (int j = 0; j <= segments; ++j) {
            float u = j / (float)segments;
            float theta = u * 2.0f * glm::pi<float>();

            float x = radius * cosf(theta) * sinf(phi);
            float y = halfHeight + radius * cosf(phi);  // 偏移到上半部
            float z = radius * sinf(theta) * sinf(phi);

            glm::vec3 pos(x, y, z);
            glm::vec3 normal = glm::normalize(glm::vec3(x, y - halfHeight, z));  // 法线相对于球心
            vertices.push_back({pos, normal, {1.0f, 1.0f, 1.0f}, {u, v}});
        }
    }

    // 下半球部分（从 y = -halfHeight 到 y = 0）
    for (int i = 0; i <= capStacks; ++i) {
        float v = 0.5f + i / (float)capStacks * 0.5f;  // 下半球，phi 从 pi/2 到 pi
        float phi = (v - 0.5f) * glm::pi<float>() + glm::pi<float>() / 2;
        for (int j = 0; j <= segments; ++j) {
            float u = j / (float)segments;
            float theta = u * 2.0f * glm::pi<float>();

            float x = radius * cosf(theta) * sinf(phi);
            float y = -halfHeight + radius * cosf(phi);  // 偏移到下半部
            float z = radius * sinf(theta) * sinf(phi);

            glm::vec3 pos(x, y, z);
            glm::vec3 normal = glm::normalize(glm::vec3(x, y + halfHeight, z));  // 法线相对于球心
            vertices.push_back({pos, normal, {1.0f, 1.0f, 1.0f}, {u, v}});
        }
    }

    // 中间圆柱部分
    for (int i = 0; i <= segments; ++i) {
        float u = i / (float)segments;
        float theta = u * 2.0f * glm::pi<float>();
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));
        
        vertices.push_back({{x, halfHeight, z}, normal, {1.0f, 1.0f, 1.0f}, {u, 1.0f}});
        vertices.push_back({{x, -halfHeight, z}, normal, {1.0f, 1.0f, 1.0f}, {u, 0.0f}});
    }

    // 上半球索引
    for (int i = 0; i < capStacks; ++i) {
        for (int j = 0; j < segments; ++j) {
            int a = i * (segments + 1) + j;
            int b = a + 1;
            int c = (i + 1) * (segments + 1) + j;
            int d = c + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(c);
        }
    }

    // 下半球索引
    int offset = (capStacks + 1) * (segments + 1);
    for (int i = 0; i < capStacks; ++i) {
        for (int j = 0; j < segments; ++j) {
            int a = offset + i * (segments + 1) + j;
            int b = a + 1;
            int c = offset + (i + 1) * (segments + 1) + j;
            int d = c + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(c);
        }
    }

    // 侧面索引
    offset = 2 * (capStacks + 1) * (segments + 1);
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        // 第一个三角形
        indices.push_back(offset + i * 2);      // 当前顶
        indices.push_back(offset + next * 2);   // 下一个顶
        indices.push_back(offset + i * 2 + 1);  // 当前底
        // 第二个三角形
        indices.push_back(offset + next * 2);   // 下一个顶
        indices.push_back(offset + next * 2 + 1); // 下一个底
        indices.push_back(offset + i * 2 + 1);  // 当前底
    }
}

// 生成圆锥体
/*
圆锥体 (Cone)
    结构：一个圆形底面收敛到一个顶点。

    参数：
        radius：底面半径。

        height：锥体高度。

        segments：底面圆周分段数。

    实现：生成底面中心和圆周顶点，以及一个顶点。底面法线向下，侧面法线根据边缘方向计算。

    索引：底面为扇形三角形，侧面为从底面到顶点的三角形。
*/
void MeshFactory::createCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
                        float radius, float height, int segments) {
    vertices.clear();
    indices.clear();

    // 底面中心
    vertices.push_back({{0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}});

    // 底面圆周和侧面顶点
    for (int i = 0; i <= segments; ++i) {
        float u = i / (float)segments;
        float theta = u * 2.0f * glm::pi<float>();
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        // 底面顶点
        vertices.push_back({{x, 0.0f, z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {cosf(theta) * 0.5f + 0.5f, sinf(theta) * 0.5f + 0.5f}});
        // 侧面法线（从底部指向顶点）
        glm::vec3 pos(x, 0.0f, z);
        glm::vec3 apex(0.0f, height, 0.0f);
        glm::vec3 edge = apex - pos;
        glm::vec3 normal = glm::normalize(glm::cross(edge, glm::vec3(-z, 0.0f, x)));
        vertices.push_back({{x, 0.0f, z}, normal, {1.0f, 1.0f, 1.0f}, {u, 0.0f}});
    }

    // 顶点
    vertices.push_back({{0.0f, height, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}});

    // 底面索引
    for (int i = 0; i < segments; ++i) {
        indices.push_back(0);              // 底面中心
        indices.push_back(1 + i * 2);      // 当前底面顶点
        indices.push_back(1 + (i + 1) * 2);// 下一个底面顶点
    }

    // 侧面索引
    int apexIndex = vertices.size() - 1;
    for (int i = 0; i < segments; ++i) {
        indices.push_back(2 + i * 2);      // 当前侧面底点
        indices.push_back(apexIndex);      // 顶点
        indices.push_back(2 + (i + 1) * 2);// 下一个侧面底点
    }
}