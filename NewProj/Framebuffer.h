#pragma once
#include <GL/glew.h>
class Framebuffer
{
public:
	Framebuffer();

	void bind();
	void unbind();

private:
	
	unsigned int FBO_ID;

};

