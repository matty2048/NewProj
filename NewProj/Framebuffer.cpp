#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &FBO_ID);
}

void Framebuffer::Bind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);
}

void Framebuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}
