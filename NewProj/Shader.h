#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <gl/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* fragpath,const char* vertpath);
	//~Shader();
	Shader() :m_ShaderID(0) {};
	void Bind();
	void SetMat4(const char* path, glm::mat4 mat);
private:
	unsigned int m_ShaderID; //id of the shader program
};

