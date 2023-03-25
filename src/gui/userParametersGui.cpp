#include "../headers/gui.h"
#include "../headers/scene.h"
#include "../headers/logger.h"
#include "../headers/triple.h"

#include <limits.h>
#include <iostream>

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
    if (ImGui::Begin("Scene parameters", &this->show)) {
        if (ImGui::CollapsingHeader("Camera")) {
            ImGui::SliderFloat("Mouse sensivity", &camera.getMouseSensitivity(), 0.1f, 1.0f, "Mouse sensivity : %.1f");
            ImGui::SliderFloat("Camera speed", &camera.getCameraSpeed(), 1.f, 30.0f, "Camera sensivity : %.1f");
        }
        
        if (ImGui::CollapsingHeader("Scène")) {
            drawLightHeader(scene);
            drawModelHeader(scene);
            drawEffectsHeader(scene);
        }

        ImGui::Separator();

        ImGui::End();
    }
}

void UserParameters::drawEffectsHeader(Scene* scene) {
    if (ImGui::TreeNode("Effects")) {
        ImGui::SameLine(); HelpMarker("Differents effects you can add to change the render");

        ImGui::Text("Effects :");
        ImGui::Checkbox("Bloom", &scene->getBool("bloom"));
        ImGui::Separator();
        ImGui::Checkbox("Blur", &scene->getBool("blur"));
        ImGui::Separator();
        ImGui::Checkbox("Chromatic Aberation", &scene->getBool("chromaticAberation"));
        
        if (ImGui::DragFloat("Red offset", &scene->getProcessing().getChromatic().redOff, 0.01f)) {
            Shader* postProcessing = scene->getShaders().find("postProcessing")->second;
            scene->getProcessing().updateUniforms(*postProcessing);
        }
        if (ImGui::DragFloat("Green offset", &scene->getProcessing().getChromatic().greenOff, 0.01f)) {
            Shader* postProcessing = scene->getShaders().find("postProcessing")->second;
            scene->getProcessing().updateUniforms(*postProcessing);
        }
        if (ImGui::DragFloat("Blue offset", &scene->getProcessing().getChromatic().blueOff, 0.01f)) {
            Shader* postProcessing = scene->getShaders().find("postProcessing")->second;
            scene->getProcessing().updateUniforms(*postProcessing);
        }

        ImGui::Separator();
        if (ImGui::Checkbox("HDR", &scene->getProcessing().getBool("hdr"))) {
            Shader* postProcessing = scene->getShaders().find("postProcessing")->second;
            scene->getProcessing().updateUniforms(*postProcessing);
        }

        ImGui::TreePop();
    } else {
        ImGui::SameLine(); HelpMarker("Differents effects you can find in the project as bloom ...");
    }
}

void UserParameters::drawLightHeader(Scene* scene) {
    if (ImGui::TreeNode("Lights")) {
        static int selected_index = 0;
        static Light* selected_light = nullptr;

        const int maxItemsToShow = 4;

        const float item_height = ImGui::GetTextLineHeightWithSpacing();
        const float item_spacing = ImGui::GetStyle().ItemSpacing.y;
        const float list_height = item_height * maxItemsToShow + item_spacing * (maxItemsToShow - 1);

        ImGui::SameLine(); HelpMarker("Lights that have been added to the scene");
        
        ImGui::Spacing();
        if (ImGui::BeginListBox("##Lights", ImVec2(-1, list_height))) {
            for (int i = 0; i < scene->getLights().size(); i++) {
                std::string iStr = std::to_string(i);
                if (ImGui::Selectable((iStr + " | " + scene->getLights()[i]->getClassName() + "##" + iStr).c_str(), selected_index == i)) {
                    selected_index = i;
                }
            }
            ImGui::EndListBox();
        }
    
        if (selected_index >= 0 && selected_index < scene->getLights().size()) {
            ImGui::Separator();
            ImGui::Text("Properties :");
            drawSelectedLightOptions(scene->getLights()[selected_index]);
        }

        ImGui::TreePop();
    } else {
        ImGui::SameLine(); HelpMarker("Lights that have been added to the scene");
    }
}

void UserParameters::drawModelHeader(Scene* scene) {
    if (ImGui::TreeNode("Models")) {
        static int selected_index = -1;
        static Model* selected_model = nullptr;

        const int maxItemsToShow = 4;

        const float item_height = ImGui::GetTextLineHeightWithSpacing();
        const float item_spacing = ImGui::GetStyle().ItemSpacing.y;
        const float list_height = item_height * maxItemsToShow + item_spacing * (maxItemsToShow - 1);

        ImGui::SameLine(); HelpMarker("Models that have been added to the scene");
        
        if (ImGui::Button("Unselect") && selected_index >= 0) {
            scene->getModels()[selected_index]->setOutlined(false);
            selected_index = -1;
        }
        ImGui::SameLine();
        if (ImGui::Button("+")) {
            ImGui::OpenPopup("Add model");
        }
            
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Add model", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Add a model using the path\n\n");
            ImGui::Separator();

            static const size_t size = 128;
            static char buffer[size];
            ImGui::Text("Path : ");
            ImGui::SameLine();
            ImGui::InputText("##Model Path", buffer, size);

            if (ImGui::Button("OK", ImVec2(120, 0))) {
                scene->addModel(new Model(buffer, glm::vec3(0.0f, 0.0f, 0.0f)));
                memset(buffer, 0, size);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }


        ImGui::Spacing();
        if (ImGui::BeginListBox("##Models", ImVec2(-1, list_height))) {
            for (int i = 0; i < scene->getModels().size(); i++) {
                if (ImGui::Selectable(("Model " + std::to_string(i) + "##" + std::to_string(i)).c_str(), selected_index == i)) {
                    // ImGui::GetID(str)
                    if (selected_index >= 0) {
                        scene->getModels()[selected_index]->setOutlined(false);
                    }
                    selected_index = i;
                    scene->getModels()[selected_index]->setOutlined(true);
                }
            }
            ImGui::EndListBox();
        }
    
        if (selected_index >= 0 && selected_index < scene->getModels().size()) {
            ImGui::Separator();
            ImGui::Text("Properties :");
            drawSelectedModelOptions(scene->getModels()[selected_index]);

        }

        ImGui::TreePop();
    } else {
        ImGui::SameLine(); HelpMarker("Models that have been added to the scene");
    }
}

void UserParameters::drawLightPositionsSlider(Light* light) {
    if (light->hasPosition()) {
        float dragWidth = ImGui::GetWindowContentRegionWidth() / 3.0f - 40;

        float x = light->getPosition().x;
        ImGui::SetNextItemWidth(dragWidth);
        if (ImGui::DragFloat("x", &x)) {
            light->getPosition().x = x;
        }

        float y = light->getPosition().y;
        ImGui::SameLine();
        ImGui::SetNextItemWidth(dragWidth);
        if (ImGui::DragFloat("y", &y)) {
            light->getPosition().y = y;
        }

        float z = light->getPosition().z;
        ImGui::SameLine();
        ImGui::SetNextItemWidth(dragWidth);
        if (ImGui::DragFloat("z", &z)) {
            light->getPosition().z = z;
        }
    }
}

void UserParameters::drawModelPositionsSlider(Model* model) {
    float dragWidth = ImGui::GetWindowContentRegionWidth() / 3.0f - 40;

    static float x = model->getPosition().x;
    ImGui::SetNextItemWidth(dragWidth);
    ImGui::DragFloat("x", &x, 0.05f);

    static float y = model->getPosition().y;
    ImGui::SameLine();
    ImGui::SetNextItemWidth(dragWidth);
    ImGui::DragFloat("y", &y, 0.05f);

    static float z = model->getPosition().z;
    ImGui::SameLine();
    ImGui::SetNextItemWidth(dragWidth);
    ImGui::DragFloat("z", &z, 0.05f);

    model->setPosition(glm::vec3(x,y,z));
}

void UserParameters::drawSelectedLightOptions(Light* light) {

    ImGui::Checkbox("Active", &light->getActive());

    std::vector<Triple<std::string, std::string, float &>> options = light->getOptions();
            
    ImGui::ColorEdit3("color 3", value_ptr(light->getColor()));
    drawLightPositionsSlider(light);
    
    for (Triple<std::string, std::string, float&>& option : options) {
        ImGui::SliderFloat(option.first().c_str(), &option.third(), 0.0f, 1.0f);
        ImGui::SameLine(); HelpMarker(option.second().c_str());
    }
}

void UserParameters::drawSelectedModelOptions(Model* model) {
    ImGui::Checkbox("Render", &model->getActive());
    
    drawModelPositionsSlider(model);

    static float scale = model->getScale();
    if (ImGui::SliderFloat("Scale", &scale, 0.0f, 50.0f)) {
        model->setScale(scale);
    }
    

}
