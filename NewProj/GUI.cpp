#include "GUI.h"
#include <Windows.h>
#include <shobjidl.h> 
#include <shlobj_core.h>
#include <sstream>

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
	ImGuiWindowFlags flags(ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_MenuBar);
	ImGui::SetNextWindowSize(ImVec2(Renderer::Size_x * 0.3, Renderer::Size_y)); //sets the position and size of the entity tree window
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("EntityWindow",nullptr,flags);
	ImGui::BeginMenuBar();
	if (ImGui::Button("Add")) {
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							
							
							std::wstring w(pszFilePath);
							const std::string s(w.begin(), w.end());
							std::cout << s;
							ents.emplace_back(std::make_shared<ModelEntity>(s.c_str()));
							
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}


	}
	ImGui::EndMenuBar();
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
			if (ImGui::SmallButton("X")) { ents.erase(ents.begin() + i); ents.shrink_to_fit(); }
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

