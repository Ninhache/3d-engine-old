#include "../headers/gui.h"

UserParameters::UserParameters(bool show) : DefaultGui() {
	this->show = show;
}

void UserParameters::render() {
    std::cout << "TEST" << std::endl;
    ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    ImGui::End();
}