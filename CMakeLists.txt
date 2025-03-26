cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置构建输出目录（覆盖默认的多配置路径）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GLFW 配置（作为单独的目标）
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glfw)
set(GLFW_LIB ${CMAKE_BINARY_DIR}/lib/glfw3.lib)

# 检查 GLFW 静态库是否已存在
if(NOT EXISTS ${GLFW_LIB})
    message(STATUS "GLFW library not found, building it...")
    add_subdirectory(${GLFW_DIR})
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
else()
    message(STATUS "GLFW library found at ${GLFW_LIB}, skipping build.")
    add_library(glfw STATIC IMPORTED)
    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION ${GLFW_LIB}
    )
endif()

# 包含目录
include_directories(
    include
    thirdparty/glad/include
    thirdparty/glfw/include
    thirdparty/glm
)

# GLAD 源文件
file(GLOB_RECURSE GLAD_SOURCES thirdparty/glad/src/glad.c)

# 添加可执行文件
add_executable(LearnOpenGL 
    src/main.cpp 
    src/Shader.cpp 
    src/Texture.cpp 
    src/Application.cpp 
    src/Window.cpp 
    src/Mesh.cpp
    ${GLAD_SOURCES}
)
target_compile_definitions(LearnOpenGL PRIVATE GLAD_GL=1)

# 强制设置输出目录为 build/bin（覆盖多配置生成器）
set_target_properties(LearnOpenGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
)

# 链接库
target_link_libraries(LearnOpenGL glfw)
target_link_libraries(LearnOpenGL ${CMAKE_DL_LIBS})

# 拷贝资源文件到构建目录
add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/bin/shaders
)

add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/bin/resources
)
