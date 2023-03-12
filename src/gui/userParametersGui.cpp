#include "../headers/gui.h"
#include "../headers/scene.h"
#include "headers/logger.h"

UserParameters::UserParameters(bool show) : DefaultGui() {
	this->show = show;
}

void showLightOptions(Light* light) {
    // Récupération des options de la lumière sélectionnée
    auto options = light->getOptions();

    // Affichage des sliders pour chaque option
    for (const auto& option : options) {
        ImGui::SliderFloat(option.first.c_str(), &option.second, 0.0f, 1.0f);
    }
}


void UserParameters::render(Scene* scene) {
    ImGui::Begin("Scene parameters", &this->show);
    ImGui::Text("Camera");
    ImGui::SliderFloat("Mouse sensivity", &camera.getMouseSensitivity(), 0.1f, 1.0f, "Mouse sensivity : %.1f");
    ImGui::SliderFloat("Camera speed", &camera.getCameraSpeed(), 1.f, 30.0f, "Camera sensivity : %.1f");
    ImGui::Separator();
    ImGui::Text("Scène");

    /*
    // Old method, not deleted atm
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
    */

    static int selectedLightIndex = 0;
    const char* items[scene->getLights().size()];

    for (size_t i = 0; i < scene->getLights().size(); i++) {
        items[i] = scene->getLights()[i]->getClassName().c_str();
    }

    ImGui::ListBox("Lights", &selectedLightIndex, items, scene->getLights().size());
    Light* selectedLight = scene->getLights()[selectedLightIndex];
    
    showLightOptions(selectedLight);


    /*
    // POUR ITERER SUR LES OPTIONS :

    // Boucle for-each pour afficher les clés et les valeurs
    for (const auto& option : options) {
        std::cout << "Key: " << option.first << ", Value: " << option.second << std::endl;
    }

    // Boucle for pour afficher les clés et les valeurs
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "Key: " << options[i].first << ", Value: " << options[i].second << std::endl;
    }
    */


    ImGui::Text("Slider Intensité light");
    ImGui::Text("Bouton open pour changer le modèle");
    ImGui::Text("Button on/off skybox");
    ImGui::Text("Bouton open pour changer la skybox / couleur du fond");

    ImGui::End();
}