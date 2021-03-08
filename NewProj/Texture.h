#pragma once
#include <iostream>
#include <string>
#include <map>
#include <GL/glew.h>
#include <assimp/material.h>

class Texture
{
public:
	Texture(unsigned int size_x,unsigned int size_y); //create empty texture with size 
	Texture(const char* path); //create texture from path
	Texture() {};
	void ChangeSize(unsigned int new_x,unsigned int new_y);
	unsigned int GetSize_x() { return size_x; };
	unsigned int GetSize_y() { return size_y; };
	unsigned int GetTexID() { return *TexID; };
	aiTextureType type;
	bool finished = false;
	void LoadTex(); //loads a texture 
	unsigned int* TexID = new(unsigned int);
private:
	//std::string path;
	unsigned int size_x;
	unsigned int size_y;
	unsigned char* data;
	static std::map<const char*,Texture*> texes;
};

