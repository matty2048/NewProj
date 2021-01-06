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
	queueitem item = { deletemesh, this->VAO, this->VBO, this->EBO, this->verticies, this->indices,this->textures };
	Renderer::additem(item);
}

Texture* Mesh::GetTex(int i)
{
	if (numtex == 0) return new Texture();
	if (textures[i]->finished)
	{
		return textures[i];
	}
	else
	{
		return new Texture();
	}

}
