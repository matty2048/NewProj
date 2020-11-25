
#include "Entity.h"
Shader Renderer::currentshader;
std::map<const char*, std::weak_ptr<Model>> ModelEntity::modelcache;


ModelEntity::ModelEntity(const char* path)
{
	if (modelcache.find(path) != modelcache.end())
	{
		if (!modelcache[path].expired()) { 
			this->model = modelcache[path].lock(); 
		}
		else
		{
			this->model = std::make_shared<Model>(path);
			modelcache.emplace(path,this->model);
		}
	}
	else
	{
		this->model = std::make_shared<Model>(path);
		modelcache.emplace(path,this->model);
	}
	CreateMatrix();
	this->type = " Model";
}

void ModelEntity::OnUpdate()
{
	//CreateMatrix();
	Renderer::currentshader.setmat4("model",transform);
	Renderer::currentshader.bind();
	this->model->Draw(); //draws the model
	
}

void ModelEntity::DoGUI()
{
	if (ImGui::SliderFloat3("translate", this->translate, -10, 10) |
		ImGui::SliderFloat3("rotate", this->rotate, -6.28, 6.28) |
		ImGui::SliderFloat3("scale", this->scale, 0, 10)) this->CreateMatrix();
}

void ModelEntity::CreateMatrix()
{
	transform = glm::mat4(1.0);
	transform *= glm::translate(glm::mat4(1.0), glm::vec3(this->translate[0], this->translate[1], this->translate[2]));
	transform *= glm::rotate(glm::mat4(1.0), this->rotate[0], glm::vec3(1.0, 0.0, 0.0));
	transform *= glm::rotate(glm::mat4(1.0), this->rotate[1], glm::vec3(0.0, 1.0, 0.0));
	transform *= glm::rotate(glm::mat4(1.0), this->rotate[2], glm::vec3(0.0, 0.0, 1.0));
	transform *= glm::scale(glm::mat4(1.0), glm::vec3(this->scale[0], this->scale[1], this->scale[2]));
}

CameraEntity::CameraEntity(Camera cam):camera(cam)
{
	this->type = " Camera";
	CreateMatrix();
}



CameraEntity::CameraEntity(glm::vec3 pos, glm::vec3 target, float fov)
{
	this->target[0] = target.x;
	this->target[1] = target.y;
	this->target[2] = target.z;

	this->positon[0] = pos.x;
	this->positon[1] = pos.y;
	this->positon[2] = pos.z;

	this->fov = fov;

	CreateMatrix();
	this->type = " Camera";
}

void CameraEntity::OnUpdate()
{
	if (this->camera.bound) camera.bind();
}

void CameraEntity::DoGUI()
{
	if (ImGui::SliderFloat("FOV", &this->fov, 0, 90) ||
		ImGui::SliderFloat3("Target", this->target, -5, 5) ||
		ImGui::SliderFloat3("Position", this->positon, -5, 5)
		) CreateMatrix();
	if (ImGui::Button("Bind Camera"))
	{
		this->camera.bound = !this->camera.bound;
	}
}

void CameraEntity::CreateMatrix()
{
	this->camera.projection = glm::perspective(glm::radians(this->fov), (float)Renderer::Size_x / (float)Renderer::Size_y, 1.0f, -100000.0f);
	this->camera.transform = glm::lookAt(glm::vec3(this->target[0], this->target[1], this->target[2]), 
	glm::vec3(this->positon[0], this->positon[1], this->positon[2]), glm::vec3(0.0f, 1.0f, 0.0f));
}
