
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

CameraEntity::CameraEntity(glm::vec3 pos, glm::vec3 target, float fov) : fov(fov)
{
	target[0] = target.x;
	target[1] = target.y;
	target[2] = target.z;

	positon[0] = pos.x;
	positon[1] = pos.y;
	positon[2] = pos.z;
}

void CameraEntity::DoGUI()
{
	//if(ImGui::SliderFloat("fov",&this->fov,0,90)|

}
