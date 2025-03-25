cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW配置
add_subdirectory(thirdparty/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 包含目录
include_directories(
    include
    thirdparty/glad/include
    thirdparty/glfw/include
    thirdparty/glm
)

# 添加可执行文件
add_executable(LearnOpenGL src/main.cpp src/Shader.cpp src/Texture.cpp src/Application.cpp src/Window.cpp)
target_compile_definitions(LearnOpenGL PRIVATE GLAD_GL=1)

# 链接库
target_link_libraries(LearnOpenGL glfw)
target_link_libraries(LearnOpenGL ${CMAKE_DL_LIBS})

# GLAD源文件
file(GLOB_RECURSE GLAD_SOURCES thirdparty/glad/src/glad.c)
target_sources(LearnOpenGL PRIVATE ${GLAD_SOURCES})

# 拷贝资源文件到构建目录
add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/Release/shaders
)

add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/Release/resources
)
