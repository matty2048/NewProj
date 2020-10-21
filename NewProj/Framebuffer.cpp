#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &FBO_ID);
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);
}

void Framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}
