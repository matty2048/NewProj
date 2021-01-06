#include "GUI.h"

void GUI::init(GLFWwindow* window) //initializes imgui in this window
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::DoGUI(std::vector<std::shared_ptr<Entity>>& ents,const RenderBuffer& RBO) //performs GUI operations
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();		//starts the ImGUI frame
	ImGui::NewFrame();
	ViewPort(RBO);
	EntityTree(ents);

}

void GUI::RenderGUI() //renders the GUI in the window
{
	ImGui::Render();	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::EntityTree(std::vector<std::shared_ptr<Entity>>& ents)
{
	ImGuiWindowFlags flags(ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoDecoration);
	ImGui::SetNextWindowSize(ImVec2(Renderer::Size_x * 0.3, Renderer::Size_y)); //sets the position and size of the entity tree window
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("EntityWindow",nullptr,flags);
	
	for (unsigned int i=0;i<ents.size();i++)
	{
		//
		std::string nodename;
		nodename.append(std::to_string(i));	
		nodename.append(ents[i]->type);		
		//creates the name of the entity in tree

		//
		if (ImGui::TreeNode(nodename.c_str())) {
			ents[i]->DoGUI(); //draws all the required sliders/buttons for entity
			if(ImGui::SmallButton("X")) ents.erase(ents.begin() + i);
			ImGui::TreePop();	
		}
		// creates the ImGUI tree node in window
	}
		
	
	ImGui::End();
}

void GUI::ViewPort(RenderBuffer RBO)
{
	//
	ImGui::SetNextWindowPos(ImVec2(Renderer::Size_x * 0.3, 0));
	ImGui::SetNextWindowSize(ImVec2(Renderer::Size_x * 0.7, Renderer::Size_y + 10));
	ImGui::Begin("rendered view");
	ImGui::Image((void*)(intptr_t)RBO(), ImVec2(Renderer::Size_x * 0.7, Renderer::Size_y)); //creates the viewport from render buffer
	ImGui::End();
	//Draws the rendered viewport  
}

