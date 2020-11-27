#pragma once
#include "Texture.h"
#include "FrameBuffer.h"

class RenderBuffer
{
public:
	RenderBuffer(unsigned int size_x,unsigned int size_y);
	void Resize(unsigned int new_x, unsigned int new_y);
	void Bind();
	void UnBind();
	unsigned int GetTexID();
	unsigned int operator() ()
	{
		return RBO_ID;
	}
private:
	Texture Tex;
	Framebuffer FBO;
	unsigned int RBO_ID;
};

