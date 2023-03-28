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
		 * @brief render the actual gui, the gui can needs access to a scene, that's why she's passed as parameters
		 * the whole structure of a GUI is defined in the render function and is always similar :
		 * 
		 * A Begin method : (takes the windows name as argument and a boolean to handle close event)
		 * ImGui::Begin("Window's name", &bool);
		 * 
		 * A Body (optional):  
		 * Can be many things (see the Dear ImGui docs for more "things")
		 * ImGui::Text("Hello world!");
		 * 
		 * An end method :
		 * Care ! you need as many Begin methods as end methods.
		 * ImGui::End();
		 * 
		 * @param scene
		*/
		virtual void render(Scene*);

		/**
		 * @brief used to know if the current gui should be drawn
		*/
		bool isShowing() { return this->show; }

	private:
		// Childs list
		std::vector<DefaultGui*> uiList;
		
	protected:
		bool show;
};

class UserParameters : public DefaultGui {
	public:
		UserParameters(bool);
		void render(Scene*);
	private:
		/**
		 * @brief draw the cursors to manage the position of the lights
		 * if the light has no position, the cursors will not be drawn
		 *
		 * @param light - The light
		 */
		void drawLightPositionsSlider(Light*);

		/**
		 * @brief draw the cursors to manage the position of the model
		 *
		 * @param model - The model
		 */
		void drawModelPositionsSlider(Model*);

		/**
		 * @brief draw the "Light Section"
		 * 
		 * @param scene - The scene
		*/
		void drawLightHeader(Scene* scene);

		/**
		 * @brief draw the "Model Section"
		 * 
		 * @param scene - The scene
		*/
		void drawModelHeader(Scene* scene);

		/**
		 * @brief draw the "Effects Section"
		 * 
		 * @param scene - The scene
		*/
		void drawEffectsHeader(Scene* scene);
};

#endif // GUI_HEADER_FILE