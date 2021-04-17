//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

#include "GLErrorManager.h"

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

//#include "Texture.h"

#include "ImGuiHandler.h"
#include "GLFWHandler.h"

#include "plato.h"



int main(void)
{
    GLFWHandler glfwhandler;
    GLFWwindow* window = glfwhandler.GetWindow();

//    TODO: not working with vec4?
    plato triangle;

    //define vertex buffer layout
    VertexBufferLayout layout = triangle.GetVertexBufferLayout();

//// Add triangle
    float center[2] = {0.0f, 0.0f};
    float length = 1.0f;
    float angle = 0.0f;
    float color[4] = {1.0f, 0.5f, 0.0f, 0.0f};
    triangle.PushColored2DTriangle(center, length, angle, color);

////Set Indices for triangles
    unsigned int corner_indices[3] = {0, 1, 2};
    triangle.PushIndices(corner_indices, 3);


    void* data_ptr = triangle.GetDataPtr();
    unsigned int* indices_ptr = triangle.GetIndicesPtr();

    // define vertex array object
    VertexArray va;

    // define vertexbuffer object

    VertexBuffer vb(data_ptr, triangle.GetDataSize());

    //link vertexbuffer to vertexarray
    va.AddBuffer(vb, layout);
    va.Bind();

    //define indexbuffer
    IndexBuffer ib(indices_ptr, triangle.GetIndexCount());


    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.0), 0.f, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 mvp = proj * view * model;

    const std::string shadersourcefilepath = "src/res/shaders/Basic.shader";
    Shader shader(shadersourcefilepath);
    shader.Bind();

    va.Bind();


    shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 0.0f);

    va.Unbind();
    shader.Unbind();
    va.Unbind();
    vb.Unbind();

    Renderer renderer;


    ImGuiHandler imguihandler(window);
    imguihandler.AddFloatSlider("my_float", 0.0f, 1.0f);

    /* Loop until the user closes the window */



    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        imguihandler.ImGuiNewFrame();

        shader.Bind();
        va.Bind();
        ib.Bind();

        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);

        shader.Unbind();

        imguihandler.ImGuiRender();

        glfwhandler.SwapBuffers();


    }


    return 0;
}