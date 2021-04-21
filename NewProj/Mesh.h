#pragma once
#include <glm/glm.hpp>
#include "Renderer.h"

class Mesh
{
public:

	Mesh(std::vector<vertex>& vertin, std::vector<unsigned int>& indcin,std::vector<Texture*> texin); //constructor for the mesh adds vao to queue
	~Mesh();
	void ReleaseMesh();
	Texture* GetTex(int i); //gets the i'th texture 
	unsigned int numindices ;
	unsigned int numtex ;
	unsigned int* VAO = new unsigned int; 	
	
private:
	std::vector<vertex> verticies;
	std::vector<unsigned int>indices;
	std::vector<Texture*> textures;

	unsigned int* VBO = new unsigned int;
	unsigned int* EBO = new unsigned int;
};

