//
// Created by sriney on 4/16/21.
//

#include "ImGuiHandler.h"

ImGuiHandler::ImGuiHandler(GLFWwindow* window) {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 130");

}

void ImGuiHandler::ImGuiNewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

ImGuiHandler::~ImGuiHandler() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiHandler::ImGuiRender() {
    {
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        for (int i_slider = 0; i_slider < m_SliderTypes.size(); i_slider++)
        {
            ImGuiSlider slider = m_SliderTypes[i_slider];
            ImGui::SliderFloat((slider.name).c_str(), &(slider.value), slider.min, slider.max);
        }


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHandler::AddFloatSlider(std::string name, float min, float max) {
    ImGuiSlider new_slider;
    new_slider.name = name;
    new_slider.min = min;
    new_slider.max = max;
    m_SliderTypes.push_back(new_slider);
}



