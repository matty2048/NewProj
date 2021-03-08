#include "Mesh.h"

Mesh::Mesh(std::vector<vertex>& vertin, std::vector<unsigned int>& indcin, std::vector<Texture*> texin)
{
	std::cout << "mesh constructed" << std::endl;
	
	this->indices = indcin;
	this->verticies = vertin;
	this->numindices = indcin.size();
	this->textures = texin;
	this->numtex = textures.size();
	
	queueitem item = {loadmesh,this->VAO,this->VBO,this->EBO,this->verticies,this->indices,this->textures};
	
	//queueitem item = {this};
	std::lock_guard<std::mutex> lck(Renderer::lock);
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

//this is moderately inefficient
void Mesh::ReleaseMesh()
{
	queueitem item = { deletemesh, this->VAO, this->VBO, this->EBO, this->verticies, this->indices,this->textures };
	std::lock_guard<std::mutex> lck(Renderer::lock);
	Renderer::additem(item);
}


Texture* Mesh::GetTex(int i)
{
	if (numtex == 0 || textures.size() == 0) return nullptr;
	
	if (textures[i]->finished)
	{
			return textures[i];
	}
	else
	{
			return nullptr;
	}
}
