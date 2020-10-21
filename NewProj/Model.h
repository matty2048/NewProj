#pragma once
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <thread>
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
class Model
{
public:
	Model(const char* path); //starts a thread to load model then fucks off
	~Model() {
		std::cout << "deconstructed model" << std::endl;
		for (unsigned int i=0;i<meshes.size();i++)
		{
			meshes[i].releasemesh();
		}
	};
	void Draw(); //draws the meshes //might not if data hasnt loaded yet
	
private:
	std::vector<Mesh> meshes; //a bunch of meshes to be drawn
	void import(const char* path); //dispatched on model creation
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

