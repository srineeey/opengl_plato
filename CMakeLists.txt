cmake_minimum_required(VERSION 3.15)
project(platonic_opengl)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/imgui)

include_directories(${OPENGL_INCLUDE_DIRS})

set(SRC_DIR src)
set(BUILD_DIR build)

add_subdirectory(${SRC_DIR}/glew)
add_subdirectory(${SRC_DIR}/glfw)
add_subdirectory(${SRC_DIR}/vendor/glm)


set(SRC_FILES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Renderer.h ${SRC_DIR}/Renderer.cpp
        ${SRC_DIR}/VertexBuffer.cpp ${SRC_DIR}/VertexBuffer.h
        ${SRC_DIR}/IndexBuffer.cpp ${SRC_DIR}/IndexBuffer.h
        ${SRC_DIR}/VertexArray.cpp ${SRC_DIR}/VertexArray.h
        ${SRC_DIR}/VertexBufferLayout.cpp ${SRC_DIR}/VertexBufferLayout.h
        ${SRC_DIR}/Shader.cpp ${SRC_DIR}/Shader.h ${SRC_DIR}/GLErrorManager.h
        ${SRC_DIR}/Texture.cpp ${SRC_DIR}/Texture.h
        ${SRC_DIR}/tests.cpp ${SRC_DIR}/tests.h
        src/ImGuiHandler.cpp src/ImGuiHandler.h src/GLFWHandler.cpp src/GLFWHandler.h src/plato.cpp src/plato.h)


add_library(stb_image
        ${SRC_DIR}/vendor/stb_image/stb_image.h  ${SRC_DIR}/vendor/stb_image/stb_image.cpp)


add_library(imgui
        ${SRC_DIR}/vendor/imgui/imgui.h ${SRC_DIR}/vendor/imgui/imgui.cpp
        ${SRC_DIR}/vendor/imgui/imconfig.h
        ${SRC_DIR}/vendor/imgui/imgui_demo.cpp
        ${SRC_DIR}/vendor/imgui/imgui_draw.cpp
        ${SRC_DIR}/vendor/imgui/imgui_impl_glfw.h ${SRC_DIR}/vendor/imgui/imgui_impl_glfw.cpp
        ${SRC_DIR}/vendor/imgui/imgui_impl_opengl3.h ${SRC_DIR}/vendor/imgui/imgui_impl_opengl3.cpp
        ${SRC_DIR}/vendor/imgui/imgui_internal.h
        ${SRC_DIR}/vendor/imgui/imgui_tables.cpp
        ${SRC_DIR}/vendor/imgui/imgui_widgets.cpp
        ${SRC_DIR}/vendor/imgui/imstb_rectpack.h
        ${SRC_DIR}/vendor/imgui/imstb_textedit.h
        ${SRC_DIR}/vendor/imgui/imstb_truetype.h
        )

add_executable(platonic_opengl ${SRC_FILES})

file(COPY ${SRC_DIR}/res/shaders/Basic.shader DESTINATION src/res/shaders)



target_link_libraries(platonic_opengl
        ${OPENGL_LIBRARIES}
        glfw
        libglew_static
        stb_image
        imgui
        glm
        )
