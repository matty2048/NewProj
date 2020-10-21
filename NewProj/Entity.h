#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <map>
#include <imgui.h>
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

class Entity
{
public:
	Entity() {};
	virtual void OnUpdate() {};
	virtual void DoGUI() {};
	glm::mat4 GetMatrix() {};
	
private:
	virtual void CreateMatrix() {}; 
protected:
	glm::mat4 transform; //used for either model or view matrix depends
	
	
};


class ModelEntity :public Entity
{
public:
	
	ModelEntity(std::shared_ptr<Model> modl) :model(modl) { CreateMatrix(); };
	ModelEntity(const char* path);
	virtual void OnUpdate() override; //called to draw
	virtual void DoGUI() override;
private:
	virtual void CreateMatrix() override; //called before draw
	float translate[3] = {0,0,0};
	float rotate[3] = { 0,0,0 };
	float scale[3] = { 0.01,0.01,0.01 };
	std::shared_ptr<Model> model;
	static std::map<const char*, std::weak_ptr<Model>> modelcache;
};


class CameraEntity : Entity,Camera
{
public:
	CameraEntity(glm::vec3 pos, glm::vec3 target,float fov);
	virtual void OnUpdate() override {};
	virtual void DoGUI() override;
private:
	float fov;
	float target[3];
	float positon[3];

};