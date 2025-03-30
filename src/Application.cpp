#include "Application.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "InputHandler.h"

Application::Application() {
    initialize();
}

Application::~Application() {}

void Application::initialize() {
    // Initialize window and ECS manager
    m_window = std::make_unique<Window>(1600, 900, "LearnOpenGL");
    m_ecs = std::make_unique<ECSManager>();

    // Create and configure renderer entity
    m_rendererEntity = m_ecs->createEntity();
    auto shader = std::make_shared<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");
    auto texture = std::make_shared<Texture>("resources/texture.png");
    
    // Create and configure camera entity
    m_cameraEntity = m_ecs->createEntity();
    auto cameraComp = m_cameraEntity->addComponent<CameraComponent>();
    cameraComp->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    
    auto renderSystem = m_ecs->addSystem<RenderSystem>(m_cameraEntity);

    // Create and configure cube entity
    auto cubeEntity = m_ecs->createEntity();
    auto transform = cubeEntity->addComponent<TransformComponent>();
    transform->position = glm::vec3(0.0f, 0.0f, 0.0f);
    cubeEntity->addComponent<MaterialComponent>(shader, texture);

    std::vector<Vertex> vertices = {
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
    std::vector<unsigned int> indices = {
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


    // Add mesh to cube and register with render system
    cubeEntity->addComponent<MeshComponent>(vertices, indices);
    renderSystem->registerEntity(cubeEntity);

    // Initialize input handler
    m_inputHandler = std::make_unique<InputHandler>(m_window->getNativeWindow(), cameraComp, renderSystem);

    // Set window user pointer for callbacks
    m_window->setUserPointer(this);

    // Mouse movement callback
    static float lastX = 800.0f;
    static float lastY = 450.0f; // Adjusted to match window height
    static bool firstMouse = true;

    m_window->setCursorCallback([](GLFWwindow* window, double xpos, double ypos) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        float x = static_cast<float>(xpos);
        float y = static_cast<float>(ypos);

        if (firstMouse) {
            lastX = x;
            lastY = y;
            firstMouse = false;
        }

        float xoffset = x - lastX;
        float yoffset = lastY - y; // Reversed since y-coordinates are bottom-to-top
        lastX = x;
        lastY = y;

        if (app->m_cameraEntity) {
            if (auto camera = app->m_cameraEntity->getComponent<CameraComponent>()) {
                camera->processMouseMovement(xoffset, yoffset);
            }
        }
    });

    // Framebuffer resize callback
    m_window->setFramebufferSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

void Application::run() {
    while (!m_window->shouldClose()) {
        // Process input
        m_inputHandler->processInput();

        // Get window dimensions
        int width, height;
        m_window->getSize(&width, &height);

        // Clear screen
        m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);

        // Update camera projection
        if (auto camera = m_cameraEntity->getComponent<CameraComponent>()) {
            camera->updateProjectionMatrix(width, height);
        }

        // Update ECS systems
        m_ecs->update(0.0f);

        // Swap buffers and poll events
        m_window->swapBuffers();
        m_window->pollEvents();
    }
}