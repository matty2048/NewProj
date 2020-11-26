#pragma once
#include <GL/glew.h>
class Framebuffer
{
public:
	Framebuffer();

	void Bind();
	void UnBind();

private:
	
	unsigned int FBO_ID;

};

