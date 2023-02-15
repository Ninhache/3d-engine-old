#pragma once

#include <vector>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "logger.h"


class DefaultGui {
	public:
		DefaultGui(bool show = false, std::vector<DefaultGui*> list = {});
		void init(GLFWwindow* window);
		void shutdown();
		virtual void render();
		bool isShowing() { return this->show; }

	private:
		std::vector<DefaultGui*> uiList;
		
	protected:
		bool show;
};

class UserParameters : public DefaultGui {
	public:
		UserParameters(bool);
		void render();
};

class SceneParameters : public DefaultGui {
	public:
		SceneParameters(bool);
		void render();
};