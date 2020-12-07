#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(unsigned int size_x,unsigned int size_y); //create empty texture with size 
	Texture(const char* path); //create texture from path

	void ChangeSize(unsigned int new_x,unsigned int new_y);
	unsigned int GetSize_x() { return size_x; };
	unsigned int GetSize_y() { return size_y; };
	unsigned int GetTexID() { return TexID; };
private:
	unsigned int TexID;
	unsigned int size_x;
	unsigned int size_y;
};

