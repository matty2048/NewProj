#include "Model.h"

Model::Model(const char* path)
{
	std::cout << "constructed model" << std::endl;
	std::thread(&Model::import, this, path).detach();
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
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |aiProcessPreset_TargetRealtime_Fast);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	

	ProcessNode(scene->mRootNode, scene);
	return;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back((ProcessMesh(mesh,scene)));
		
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertex> verticies;
	std::vector<unsigned int> indicies;

	vertex Vertex;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		Vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		verticies.push_back(Vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int ii = 0; ii < face.mNumIndices; ii++){
			indicies.push_back(face.mIndices[ii]);
		}
	}
	return Mesh(verticies,indicies);
}
