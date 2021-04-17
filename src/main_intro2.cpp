//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include "GLErrorManager.h"

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_opengl3.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew not ok\n";
    else
        std::cout << "glew ok\n";

    std::cout << glGetString(GL_VERSION);


    /*
     * Define Buffer here
     */

    float positions[] =
            {
            -0.5f,-0.5f, 0.0f, 0.0f,
            0.5f,-0.5f, 1.0f, 0.0f,
            0.5f,0.5f, 1.0f, 1.0f,
            -0.5f,0.5f, 0.0f, 1.0f,
            };

    const unsigned int indices[] =
                         {
            0,1,2,
            2,3,0
                         };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

//    unsigned int vao;
//    GLCall(glGenVertexArrays(1, &vao));
//    GLCall(glBindVertexArray(vao));

    // define vertex array object
    VertexArray va;

    // define vertexbuffer object
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    //define vertexbuffer layout
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    //link vertexbuffer to vertexarray
    va.AddBuffer(vb, layout);
    va.Bind();

    //define indexbuffer
    IndexBuffer ib(indices, 3*2);

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.2f, 0.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.0), 45.f, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 mvp = proj * view * model;

    const std::string shadersourcefilepath = "src/res/shaders/Basic.shader";
    Shader shader(shadersourcefilepath);
    shader.Bind();

    va.Bind();


    //shader.SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    //TODO: FIND PNG
    //Texture texture("res/textures/logo.png");
    Texture texture("/home/sriney/CLionProjects/opengl_yt/build/src/res/textures/logo.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture",0);
    shader.SetUniformMat4f("u_MVP", mvp);

    va.Unbind();
    shader.Unbind();
    va.Unbind();
    vb.Unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 130");

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float angle = 0.0f;
    static float angle_delta = 0.1f;
    glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
    /* Loop until the user closes the window */

    glm::vec3 rot_axis(1.0f, 1.0f, 1.0f);

    std::vector<glm::vec3> translations;
    translations.push_back(glm::vec3(1.0,0.0,0.0));
    translations.push_back(glm::vec3(-1.0,0.0,0.0));
    translations.push_back(glm::vec3(0.0,1.0,0.0));
    translations.push_back(glm::vec3(0.0,-1.0,0.0));

    while (!glfwWindowShouldClose(window))
    {
        angle += angle_delta;
        if (angle >= 360.0f )
        {
            angle -= 360.0f;
        }
        /* Render here */
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.Bind();
        va.Bind();
        ib.Bind();

        for (int i = 0; i < translations.size(); i++)
        {
            glm::mat4 trans = glm::translate(glm::mat4(1.0), translations[i]);
            glm::mat4 model = glm::rotate(trans, angle, rot_axis);
            glm::mat4 mvp = proj * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }
        shader.Unbind();

        {
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat3("axis", &(rot_axis.x), 0.0f, 1.0f);
            ImGui::SliderFloat("axis x", &(rot_axis.x), 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("axis y", &(rot_axis.y), 0.0f, 1.0f);
            ImGui::SliderFloat("axis z", &(rot_axis.z), 0.0f, 1.0f);
            ImGui::SliderFloat("angle", &angle_delta, 0.0f, 1.0f);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}