
#include "Entity.h"
Shader Renderer::currentshader;
std::map<const char*, std::weak_ptr<Model>> ModelEntity::modelcache;


ModelEntity::ModelEntity(const char* path)
{
	if (modelcache.find(path) != modelcache.end()) 
	{
		if (!modelcache[path].expired()) { 
			this->model = modelcache[path].lock(); //this returns the cached values
		}
		else //if cache expired
		{
			this->model = std::make_shared<Model>(path); //loads the model
			modelcache.emplace(path,this->model);  //adds it to the cache
		}
	}
	else //if cache misses entirely
	{
		this->model = std::make_shared<Model>(path);
		modelcache.emplace(path,this->model);
	}
	CreateMatrix(); //creates the transformation matrix
	this->type = " Model"; //changes the type of the entity
}

void ModelEntity::OnUpdate()
{
	Renderer::currentshader.Bind();
	//CreateMatrix();
	Renderer::currentshader.SetMat4("model",transform);
	Renderer::currentshader.Bind();
	this->model->Draw(); //draws the model
	
}

void ModelEntity::DoGUI()
{

	//draws the sliders for the properties section
	if (ImGui::SliderFloat3("translate", this->translate, -10, 10) |
		ImGui::SliderFloat3("rotate", this->rotation, -6.28, 6.28) |
		ImGui::SliderFloat3("scale", this->scale, 0, 10)) this->CreateMatrix();
}

void ModelEntity::CreateMatrix()
{
	//multiplies all the tranformation matricies together
	transform = glm::mat4(1.0);
	transform *= glm::translate(glm::mat4(1.0), glm::vec3(this->translate[0], this->translate[1], this->translate[2]));
	transform *= glm::rotate(glm::mat4(1.0), this->rotation[0], glm::vec3(1.0, 0.0, 0.0));
	transform *= glm::rotate(glm::mat4(1.0), this->rotation[1], glm::vec3(0.0, 1.0, 0.0));
	transform *= glm::rotate(glm::mat4(1.0), this->rotation[2], glm::vec3(0.0, 0.0, 1.0));
	transform *= glm::scale(glm::mat4(1.0), glm::vec3(this->scale[0], this->scale[1], this->scale[2]));
}

CameraEntity::CameraEntity(Camera cam):camera(cam)
{
	this->type = " Camera";
	CreateMatrix();
}



CameraEntity::CameraEntity(glm::vec3 pos, glm::vec3 target, float fov)
{
	this->rotation[0] = target.x;
	this->rotation[1] = target.y;
	this->rotation[2] = target.z;

	this->positon[0] = pos.x;
	this->positon[1] = pos.y;
	this->positon[2] = pos.z;

	this->fov = fov;

	CreateMatrix();
	this->type = " Camera";
}

void CameraEntity::OnUpdate()
{
	if (this->camera.bound) camera.Bind();
}

void CameraEntity::DoGUI()
{
	if (ImGui::SliderFloat("FOV", &this->fov, 0, 90) |
		ImGui::SliderFloat3("rotation", this->rotation, -6, 6)|
		ImGui::SliderFloat3("Position", this->positon, -5, 5)
		) CreateMatrix();

	if (this->camera.bound ? ImGui::Button("UnBind Camera"):ImGui::Button("Bind Camera"))
	{
		this->camera.bound = !this->camera.bound;
	}
}

void CameraEntity::CreateMatrix()
{
	this->camera.projection = glm::perspective(glm::radians(this->fov), (float)Renderer::Size_x / (float)Renderer::Size_y, 1.0f, -100000.0f);
	//this->camera.transform = glm::lookAt(glm::vec3(this->target[0], this->target[1], this->target[2]), 
	this->camera.transform = glm::mat4(1.0f);
	this->camera.transform *= glm::rotate(glm::mat4(1.0), this->rotation[0], glm::vec3(1.0, 0.0, 0.0));
	this->camera.transform *= glm::rotate(glm::mat4(1.0), this->rotation[1], glm::vec3(0.0, 1.0, 0.0));
	this->camera.transform *= glm::rotate(glm::mat4(1.0), this->rotation[2], glm::vec3(0.0, 0.0, 1.0));
	this->camera.transform *= glm::translate(glm::mat4(1.0f),glm::vec3(this->positon[0], this->positon[1], this->positon[2]));
}
