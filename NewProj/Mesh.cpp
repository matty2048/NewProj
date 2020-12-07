#include "Mesh.h"

//TODO: FIX unneccesarry copies in mesh data!!!

Mesh::Mesh(std::vector<vertex>& vertin, std::vector<unsigned int>& indcin)
{
	std::cout << "mesh constructed" << std::endl;
	std::lock_guard<std::mutex> lck(Renderer::lock); //creates mutex lock to avoid asynchronous problems
	this->indices = indcin; //copys the index data into the mesh
	this->verticies = vertin; //copys the vertex data into the mesh 
	this->numindices = indcin.size(); //gets the number of indices in the mesh
	
	//TODO:  this is bad and i dont like  it
	queueitem item = {loadmesh,this->VAO,this->VBO,this->EBO,this->verticies,this->indices};//saves the data so that it can be loaded into the GPU
	Renderer::additem(item); //puts the mesh data onto the synchronization stack to be delt with
	return;
	// mutex lock is then freed so other threads can access data
}

Mesh::~Mesh()
{
	std::cout << "mesh deconstructed" << std::endl;
}

void Mesh::ReleaseMesh()
{
	//this is also bad and  super unnecessary!!!!
	queueitem item = { deletemesh, this->VAO, this->VBO, this->EBO, this->verticies, this->indices }; //TODO: FIX!
	Renderer::additem(item);
}
