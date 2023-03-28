#ifndef GUI_HEADER_FILE
#define GUI_HEADER_FILE

#include <vector>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>

#include "logger.h"
#include "light.h"
#include "model.h"

class Scene;


class DefaultGui {
	public:
		DefaultGui(bool show = false, std::vector<DefaultGui*> list = {});
		void init(GLFWwindow* window);
		
		/**
		 * @brief close the library properly according to the documentation.
		*/
		void closeLibrary();

		/**
		 * @brief render the actual gui, the whole structure of a GUI is defined in the render function and is always similar :
		 * The gui can needs access to a scene, that's why she's passed as parameters
		 * 
		 * // The Begin method, taking the windows name as argument, and a boolean :
		 * // the boolean is to handle the windows close event.
		 * ImGui::Begin("Window's name", &bool);
		 * 
		 * // The structure is defined there, if you want to print a text there, use the according nodes..
		 * ImGui::Text("Hello world!");
		 * 
		 * // The end method, you've to put at the end of each GUI
		 * ImGui::End();
		 * 
		 * @param scene
		*/
		virtual void render(Scene*);

		bool isShowing() { return this->show; }

	private:
		std::vector<DefaultGui*> uiList;
		
	protected:
		bool show;
};

class UserParameters : public DefaultGui {
	public:
		UserParameters(bool);
		void render(Scene*);
		
		void drawLightPositionsSlider(Light*);
		void drawModelPositionsSlider(Model*);
		void drawSelectedLightOptions(Light*);

		void drawLightHeader(Scene* scene);
		void drawModelHeader(Scene* scene);
		void drawEffectsHeader(Scene* scene);
};

class SceneParameters : public DefaultGui {
	public:
		SceneParameters(bool);
		void render(Scene*);
};

#endif // GUI_HEADER_FILE