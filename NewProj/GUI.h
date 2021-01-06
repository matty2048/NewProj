#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Entity.h"
#include "Renderer.h"
#include "RenderBuffer.h"
#include "Texture.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class GUI
{
public:
	static void init(GLFWwindow* window);
	static void DoGUI(std::vector<std::shared_ptr<Entity>>& ents,const RenderBuffer& RBO);
	static void RenderGUI();
	static int window_x;
	static int window_y;
private:
	static void EntityTree(std::vector<std::shared_ptr<Entity>>& ents);
	static void ViewPort(RenderBuffer RBO);
	static void propertieswindow();


	Texture ViewPortTex;
};

