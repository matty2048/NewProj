#include "Model.h"

Model::Model(const char* path)
{
	std::cout << "constructed model" << std::endl;
	std::thread(&Model::import, this, path).detach();
	//import(path);
	//import(path);
}

void Model::Draw()
{
	//std::lock_guard<std::mutex> lck(Renderer::lock);
	for (int i = 0; i < meshes.size(); i++)
	{
		unsigned int nrDiff = 1;
		unsigned int nrSpec = 1;
		for (unsigned int ii = 0; ii < meshes[i].numtex; ii++)
		{
			if (meshes[i].GetTex(ii) == nullptr) break; 
			std::string CurName;
			glActiveTexture(GL_TEXTURE0 + ii);
			if (meshes[i].GetTex(ii)->type == aiTextureType_DIFFUSE)
			{
				CurName = "Diffuse" + std::to_string(nrDiff);
				Renderer::currentshader.SetInt(CurName.c_str(), ii);
		
				nrDiff += 1; //increments the number of diffuse textures
			} //diffuse texture
			if (meshes[i].GetTex(ii)->type == aiTextureType_SPECULAR)
			{
				CurName = "Spec" + std::to_string(nrSpec);
				Renderer::currentshader.SetInt(CurName.c_str(), ii);
				nrSpec += 1; //increments the number of diffuse textures
			}
			glBindTexture(GL_TEXTURE_2D,meshes[i].GetTex(ii)->GetTexID());
		}
		if (meshes[i].numtex == 0) Renderer::currentshader.SetInt("HasTex", 0);
		else Renderer::currentshader.SetInt("HasTex", 1);
		Renderer::currentshader.Bind();
		Renderer::DrawIndexed(*meshes[i].VAO, meshes[i].numindices);
		//glActiveTexture(GL_TEXTURE0);
		
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
	std::vector<Texture*> Textures;
	vertex Vertex;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		Vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->HasTextureCoords(0)) //if there are texture coords
		{
			Vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			Vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
			Vertex.TexCoords = glm::vec2(0.0);
		verticies.push_back(Vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int ii = 0; ii < face.mNumIndices; ii++){
			indicies.push_back(face.mIndices[ii]);
		}
	}
	if (mesh->mMaterialIndex >= 0) //if the mesh has materials
	{
		//std::lock_guard<std::mutex> lck(Renderer::lock);
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex]; //pointer to a material
		for (unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, i, &path); //gets the textures path
			std::cout << path.C_Str();
			Texture* t = new Texture(path.C_Str());
			
			Textures.push_back(t);
			Textures.back()->type = aiTextureType_DIFFUSE;
		} //loads the diffuse textures
		for (unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_SPECULAR, i, &path); //gets the textures path
			std::cout << path.C_Str();
			Texture* t = new Texture(path.C_Str());
			Textures.push_back(t);
			Textures.back()->type = aiTextureType_SPECULAR;
		} //loads the specular textures
	
	}

	
	
	return Mesh(verticies,indicies,Textures);
}

