#include "RenderBuffer.h"



RenderBuffer::RenderBuffer(unsigned int size_x, unsigned int size_y)
{
    this->Tex = Texture(size_x, size_y);
    glBindTexture(1, this->Tex.GetTexID());
    FBO.Bind();
    glGenRenderbuffers(1, &RBO_ID);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Tex.GetSize_x(), Tex.GetSize_y());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO_ID);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Tex.GetTexID(), 0);
    GLenum buf[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buf);
    FBO.UnBind();
}

void RenderBuffer::Resize(unsigned int new_x, unsigned int new_y)
{
    Tex.ChangeSize(new_x, new_y);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Tex.GetSize_x(), Tex.GetSize_y());   
}

void RenderBuffer::Bind()
{
    FBO.Bind();
 
    glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);

}

void RenderBuffer::UnBind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    FBO.UnBind();
}

unsigned int RenderBuffer::GetTexID()
{
    return Tex.GetTexID();
}
