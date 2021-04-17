//
// Created by sriney on 4/16/21.
//

#include "GLFWHandler.h"

GLFWHandler::GLFWHandler() {

    /* Initialize the library */
    if (!glfwInit())
//        return -1;
        std::cout << "could not initialize glfw lib\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
//        return -1;
        std::cout << "could not create window\n";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew not ok\n";
    else
        std::cout << "glew ok\n";

    std::cout << glGetString(GL_VERSION);

}

GLFWHandler::~GLFWHandler() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

GLFWwindow *GLFWHandler::GetWindow() {
    return m_Window;
}

void GLFWHandler::SwapBuffers() {
    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);

    /* Poll for and process events */
    glfwPollEvents();
}
