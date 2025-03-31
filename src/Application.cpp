#include "Application.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "InputHandler.h"
#include "MeshFactory.h"

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

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // 正方体
    auto cubeEntity = m_ecs->createEntity();
    auto transform = cubeEntity->addComponent<TransformComponent>();
    transform->position = glm::vec3(-4.0f, 0.0f, 0.0f);
    cubeEntity->addComponent<MaterialComponent>(shader, texture);
    MeshFactory::createCube(vertices, indices);  // 使用 MeshFactory 生成立方体数据
    cubeEntity->addComponent<MeshComponent>(vertices, indices);
    renderSystem->registerEntity(cubeEntity);

    // 球体
    auto sphereEntity = m_ecs->createEntity();
    auto sphereTransform = sphereEntity->addComponent<TransformComponent>();
    sphereTransform->position = glm::vec3(-2.0f, 0.0f, 0.0f);
    sphereEntity->addComponent<MaterialComponent>(shader, texture);
    MeshFactory::createSphere(vertices, indices, 0.5f, 32, 16);  // 生成球体数据
    sphereEntity->addComponent<MeshComponent>(vertices, indices);
    renderSystem->registerEntity(sphereEntity);

    // 创建胶囊体
    auto capsuleEntity = m_ecs->createEntity();
    auto capsuleTransform = capsuleEntity->addComponent<TransformComponent>();
    capsuleTransform->position = glm::vec3(0.0f, 0.0f, 0.0f);
    MeshFactory::createCapsule(vertices, indices, 0.5f, 1.0f, 32, 8);
    capsuleEntity->addComponent<MeshComponent>(vertices, indices);
    capsuleEntity->addComponent<MaterialComponent>(shader, texture);
    renderSystem->registerEntity(capsuleEntity);

    // 创建圆锥体
    auto coneEntity = m_ecs->createEntity();
    auto coneTransform = coneEntity->addComponent<TransformComponent>();
    coneTransform->position = glm::vec3(2.0f, 0.0f, 0.0f);
    MeshFactory::createCone(vertices, indices, 0.5f, 1.0f, 32);
    coneEntity->addComponent<MeshComponent>(vertices, indices);
    coneEntity->addComponent<MaterialComponent>(shader, texture);
    renderSystem->registerEntity(coneEntity);

    // 创建圆柱体
    auto cylinderEntity = m_ecs->createEntity();
    auto cylinderTransform = cylinderEntity->addComponent<TransformComponent>();
    cylinderTransform->position = glm::vec3(4.0f, 0.0f, 0.0f);
    MeshFactory::createCylinder(vertices, indices, 0.5f, 1.0f, 32);
    cylinderEntity->addComponent<MeshComponent>(vertices, indices);
    cylinderEntity->addComponent<MaterialComponent>(shader, texture);
    renderSystem->registerEntity(cylinderEntity);


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