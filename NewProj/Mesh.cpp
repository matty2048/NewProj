#include "Mesh.h"

Mesh::Mesh(std::vector<vertex>& vertin, std::vector<unsigned int>& indcin)
{
	std::cout << "mesh constructed" << std::endl;
	std::lock_guard<std::mutex> lck(Renderer::lock);
	this->indices = indcin;
	this->verticies = vertin;
	this->numindices = indcin.size();
	
	
	
	queueitem item = {loadmesh,this->VAO,this->VBO,this->EBO,this->verticies,this->indices};
	
	//queueitem item = {this};
	Renderer::additem(item);
	return;
}

Mesh::~Mesh()
{
	//delete this->VAO;
	//delete this->VBO;
	//delete this->EBO;
	std::cout << "mesh deconstructed" << std::endl;
}

void Mesh::ReleaseMesh()
{
	queueitem item = { deletemesh, this->VAO, this->VBO, this->EBO, this->verticies, this->indices };
	Renderer::additem(item);
}
