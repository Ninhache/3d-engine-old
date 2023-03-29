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

class DefaultGui
{
public:
	DefaultGui(bool show = false, std::vector<DefaultGui *> list = {});
	void init(GLFWwindow *window);

	/**
	 * @brief close the library properly according to the documentation.
	 */
	void closeLibrary();

	/**
	 * @brief Draws the GUI
	 *
	 * the whole structure of a GUI is defined in the render function and is always similar :
	 *
	 * A Begin method : (takes the windows name as argument and a boolean to handle close event) @n
	 * ImGui::Begin("Window's name", &bool);
	 *
	 * A Body (optional):
	 * Can be many things (see the Dear ImGui docs for more "things") @n
	 * ImGui::Text("Hello world!");
	 *
	 * An end method : @n
	 * ImGui::End();
	 *
	 * @note you need as many Begin methods as end methods.
	 *
	 * @param scene The scene to retrieve informations from
	 */
	virtual void render(Scene *);

	/**
	 * @brief Boolean value indicating  if the current gui should be drawn
	 *
	 * @return true If the gui should be drawn
	 * @return false If the gui should not be drawn
	 */
	bool isShowing() { return this->show; }

private:
	// Children list
	std::vector<DefaultGui *> uiList;

protected:
	bool show;
};

class UserParameters : public DefaultGui
{
public:
	UserParameters(bool);
	void render(Scene *);

	/**
	 * @brief Draws the sliders managing the position of the light
	 *
	 * @remark if the light has no position, the cursors will not be drawn
	 *
	 * @param light The light to be moved
	 */
	void drawLightPositionsSlider(Light *light);

	/**
	 * @brief Draws the slider managing the position of the model
	 *
	 * @param model The model to be moved
	 */
	void drawModelPositionsSlider(Model *model);

	/**
	 * @brief Draws the Lights interaction widget
	 *
	 * @param scene The scene to retrieve informations from
	 */
	void drawLightHeader(Scene *scene);

	/**
	 * @brief Draws the Models interaction widget
	 *
	 * @param scene The scene to retrieve informations from
	 */
	void drawModelHeader(Scene *scene);

	/**
	 * @brief Draws the Effects interaction widget
	 *
	 * @param scene The scene to retrieve informations from
	 */
	void drawEffectsHeader(Scene *scene);

	void drawSkyboxHeader(Scene *scene);
};

#endif // GUI_HEADER_FILE