//
// Created by sriney on 4/16/21.
//

#include <iostream>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


struct ImGuiSlider
{
    std::string name = "Slider";
    float value = 0.;
    float min = 0.f;
    float max = 0.f;
};


class ImGuiHandler
{
private:
    std::vector<ImGuiSlider> m_SliderTypes;

public:
    ImGuiHandler(GLFWwindow* window);

    ~ImGuiHandler();

    void ImGuiNewFrame();

    void ImGuiRender();

    void AddFloatSlider(std::string name, float min, float max);



};