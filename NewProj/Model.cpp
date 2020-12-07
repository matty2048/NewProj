#include "Model.h"

Model::Model(const char* path)
{
	std::cout << "constructed model" << std::endl;
	std::thread(&Model::import, this, path).detach(); //creates and detaches thread to load model data in
	//import(path);
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		Renderer::DrawIndexed(*meshes[i].VAO, meshes[i].numindices);
	}
}

void Model::import(const char* path)
{
	//std::lock_guard<std::mutex> lck(Renderer::lock);
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |aiProcess_GenNormals |aiProcessPreset_TargetRealtime_Fast);
	//imports the  model data + does some prostprocessing, triangulation and normal generation
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	

	ProcessNode(scene->mRootNode, scene); //starts the node processing 
	return;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		meshes.emplace_back((ProcessMesh(mesh,scene))); //processes the mesh + emplaces at back of mesh vector
		
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene); //reccurses over children
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertex> verticies;
	std::vector<unsigned int> indicies;

	vertex Vertex;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)//loops over all the verticies
	{
		Vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		//extracts the position
		Vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		//extracts the normal
		verticies.push_back(Vertex);
		//pushes to the vertex vector
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int ii = 0; ii < face.mNumIndices; ii++){
			indicies.push_back(face.mIndices[ii]);
			//extracts all the indices in the mesh
		}
	}
	return Mesh(verticies,indicies);
}
