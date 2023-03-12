#include "../headers/gui.h"
#include "../headers/scene.h"
#include "headers/logger.h"

UserParameters::UserParameters(bool show) : DefaultGui() {
	this->show = show;
}

void UserParameters::render(Scene* scene) {
    ImGui::Begin("Scene parameters", &this->show);
    ImGui::Text("Camera");
    ImGui::SliderFloat("Mouse sensivity", &camera.getMouseSensitivity(), 0.1f, 1.0f, "Mouse sensivity : %.1f");
    ImGui::SliderFloat("Camera speed", &camera.getCameraSpeed(), 1.f, 30.0f, "Camera sensivity : %.1f");
    ImGui::Separator();
    ImGui::Text("Scène");

    ImGui::BeginListBox("jsp");
    static int item_current_idx = 0;
    for (int n = 0; n < scene->getLights().size(); n++) {
        const bool is_selected = (item_current_idx == n);

        //std::string strNew = *pStr;
        auto light = scene->getLights().at(n);
        const char* type = light->getClassName().c_str();

        if (ImGui::Selectable(type, is_selected)) {
            item_current_idx = n;
        }

        if (is_selected) {
            ImGui::SetItemDefaultFocus();
        }
    }
    ImGui::EndListBox();

    ImGui::Text("Slider Intensité light");
    ImGui::Text("Bouton open pour changer le modèle");
    ImGui::Text("Button on/off skybox");
    ImGui::Text("Bouton open pour changer la skybox / couleur du fond");

    ImGui::End();
}