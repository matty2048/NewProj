#include "RenderBuffer.h"



RenderBuffer::RenderBuffer(unsigned int size_x, unsigned int size_y):Tex(size_x,size_y) //creates a renderbuffer
{
    FBO.Bind(); //binds the attached framebuffer
    glGenRenderbuffers(1, &RBO_ID); //generates renderbuffer
    glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);  //binds it
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Tex.GetSize_x(), Tex.GetSize_y()); //adds depth component 
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO_ID); //connects framebuffer & renderbuffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Tex.GetTexID(), 0); //adds texture component 
    GLenum buf[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buf);
    FBO.UnBind(); //unbinds the framebuffer
}

void RenderBuffer::Resize(unsigned int new_x, unsigned int new_y) //handles re-sizing of the window
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
