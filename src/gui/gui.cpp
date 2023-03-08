#include "../headers/gui.h"
#include "../headers/scene.h"

#include <iostream>

DefaultGui::DefaultGui(bool show, std::vector<DefaultGui*> list) {
    this->show = show;
    this->uiList = list;
}

void DefaultGui::render(Scene* scene) {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    for(auto gui : this->uiList) {
        if (gui->isShowing()) gui->render(scene);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DefaultGui::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
     
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void DefaultGui::closeLibrary() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}