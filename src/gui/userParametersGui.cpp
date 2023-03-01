#include "../headers/gui.h"
#include "../headers/scene.h"

UserParameters::UserParameters(bool show) : DefaultGui() {
	this->show = show;
}

<<<<<<< HEAD
void UserParameters::render(Scene* scene) {
    ImGui::Begin("Scene parameters", &this->show);
    ImGui::Text("Camera");
    ImGui::SliderFloat("Mouse sensivity", &scene->getCamera().getMouseSensitivity(), 0.1f, 1.0f, "Mouse sensivity : %.1f");
    ImGui::SliderFloat("Camera speed", &scene->getCamera().getCameraSensitivity(), 1.f, 30.0f, "Camera sensivity : %.1f");
    ImGui::Separator();
    ImGui::Text("Scène");
    ImGui::Checkbox("Light", &scene->getDrawLights());
    ImGui::Text("Slider Intensité light");
    ImGui::Text("Bouton open pour changer le modèle");
    ImGui::Text("Button on/off skybox");
    ImGui::Text("Bouton open pour changer la skybox / couleur du fond");

=======
void UserParameters::render() {
    ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
>>>>>>> 177b45202733dc165b233a3f3d51f91745844476
    ImGui::End();
}