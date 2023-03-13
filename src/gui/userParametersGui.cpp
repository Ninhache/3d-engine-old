#include "../headers/gui.h"
#include "../headers/scene.h"
#include "../headers/logger.h"
#include "../headers/triple.h"

#include <limits.h>

#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))     // Size of a static C-style array. Don't use on pointers!

UserParameters::UserParameters(bool show) : DefaultGui() {
	this->show = show;
}

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void UserParameters::render(Scene* scene) {
    ImGui::Begin("Scene parameters", &this->show);
    
    if (ImGui::CollapsingHeader("Camera")) {
        ImGui::SliderFloat("Mouse sensivity", &camera.getMouseSensitivity(), 0.1f, 1.0f, "Mouse sensivity : %.1f");
        ImGui::SliderFloat("Camera speed", &camera.getCameraSpeed(), 1.f, 30.0f, "Camera sensivity : %.1f");
    }
    
    if (ImGui::CollapsingHeader("Scène")) {
        static int selected_index = 0;
        static Light* selected_light = nullptr;

        const int maxItemsToShow = 3;

        const float item_height = ImGui::GetTextLineHeightWithSpacing();
        const float item_spacing = ImGui::GetStyle().ItemSpacing.y;
        const float list_height = item_height * maxItemsToShow + item_spacing * (maxItemsToShow - 1);
        

        ImGui::Text("Lights");
        ImGui::SameLine(); HelpMarker("Lights that have been added to the scene");
        
        ImGui::Spacing();
        ImGui::BeginListBox("##Lights", ImVec2(-1, list_height));
        for (int i = 0; i < scene->getLights().size(); i++) {
            if (ImGui::Selectable((scene->getLights()[i]->getClassName() + "##" + std::to_string(i)).c_str(), selected_index == i)) {
                selected_index = i;
            }
        }
        ImGui::EndListBox();
        
        if (selected_index >= 0 && selected_index < scene->getLights().size()) {
            selected_light = scene->getLights()[selected_index];

            std::vector<Triple<std::string, std::string, float &>> options = selected_light->getOptions();
            
            float dragWidth = ImGui::GetWindowContentRegionWidth() / 3.0f - 20;

            float x = selected_light->getPos().x;
            ImGui::SetNextItemWidth(dragWidth);
            if (ImGui::DragFloat("x", &x)) {
                selected_light->getPos().x = x;
            }

            float y = selected_light->getPos().y;
            ImGui::SameLine();
            ImGui::SetNextItemWidth(dragWidth);
            if (ImGui::DragFloat("y", &y)) {
                selected_light->getPos().y = y;
            }


            float z = selected_light->getPos().z;
            ImGui::SameLine();
            ImGui::SetNextItemWidth(dragWidth);
            if (ImGui::DragFloat("z", &z)) {
                selected_light->getPos().z = z;
            }


            for (Triple<std::string, std::string, float&>& option : options) {
                ImGui::SliderFloat(option.first().c_str(), &option.third(), 0.0f, 1.0f);
                ImGui::SameLine(); HelpMarker(option.second().c_str());
            }
        }
    }

    ImGui::Separator();

    ImGui::Text("Bouton open pour changer le modèle");
    ImGui::Text("Button on/off skybox");
    ImGui::Text("Bouton open pour changer la skybox / couleur du fond");

    ImGui::End();
}