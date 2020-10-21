#pragma once
#include <glm/glm.hpp>
#include "Renderer.h"

class Mesh
{
public:

	Mesh(std::vector<vertex>& vertin, std::vector<unsigned int>& indcin); //constructor for the mesh adds vao to queue
	~Mesh();
	void releasemesh();
	unsigned int numindices;
	unsigned int* VAO = new unsigned int; 	
	
private:
	std::vector<vertex> verticies;
	std::vector<unsigned int>indices;

	unsigned int* VBO = new unsigned int;
	unsigned int* EBO = new unsigned int;
};

