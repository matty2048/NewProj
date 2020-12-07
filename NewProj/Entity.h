#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <map>
#include <imgui.h>
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

class Entity //base entity class
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


class ModelEntity :public Entity //Entity class for when a model is used
{
public:
	
	ModelEntity(std::shared_ptr<Model> modl) :model(modl) { CreateMatrix(); }; //creates model entity from existing model
	ModelEntity(const char* path);  //creates model  entity from  path
	virtual void OnUpdate() override; //called to draw
	virtual void DoGUI() override;  //called to display GUI sliders
	
private:
	virtual void CreateMatrix() override; //called before draw
	float translate[3] = {0,0,0}; 
	float rotate[3] = { 0,0,0 };			//transformation components 
	float scale[3] = { 0.01,0.01,0.01 };
	std::shared_ptr<Model> model;			//shared ptr to model data
	static std::map<const char*, std::weak_ptr<Model>> modelcache; //a cache of models to avoid reloads
};


class CameraEntity :public Entity
{
public:
	CameraEntity(Camera cam);
	CameraEntity(glm::vec3 pos, glm::vec3 target, float fov);// creates and initializes a new camera entity
	virtual void OnUpdate() override; 
	virtual void DoGUI() override; //options sliders
	
private:
	float fov = { 45.0f }; 
	float rotation[3] = { 0,0,-1 };	//components of transformation matrix 
	float positon[3] = { 0,0,0 };
	
	Camera camera;  
	virtual void CreateMatrix() override;
};