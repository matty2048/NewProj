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
	std::string type;
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
	float rotation[3] = { 0,0,0 };
	float scale[3] = { 0.1,0.1,0.1 };
	std::shared_ptr<Model> model;
	static std::map<const char*, std::weak_ptr<Model>> modelcache;
};


class CameraEntity :public Entity
{
public:
	CameraEntity(Camera cam);
	CameraEntity(glm::vec3 pos, glm::vec3 target, float fov);// creates and initializes a new camera entity
	virtual void OnUpdate() override; 
	virtual void DoGUI() override; //does each update
	
private:
	float fov = { 45.0f };
	float rotation[3] = { 0,0,-1 };
	float positon[3] = { 0,0,0 };
	
	Camera camera;
	virtual void CreateMatrix() override;
};