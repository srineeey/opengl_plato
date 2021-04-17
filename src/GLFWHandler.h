//
// Created by sriney on 4/16/21.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>


class GLFWHandler
{
private:
    GLFWwindow* m_Window;
public:
    GLFWHandler();

    ~GLFWHandler();

    GLFWwindow* GetWindow();

    void SwapBuffers();

};
