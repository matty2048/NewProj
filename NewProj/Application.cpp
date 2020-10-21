#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>
#include "RenderBuffer.h"
#include "GUI.h"
#include <memory>

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

int main()
{

    GLFWwindow* window = Renderer::init(1024,1024);
    if (window == nullptr)
    {
        return -1;
    }
    GUI::init(window);
   
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    const char* path = "arch.obj";
    
    Shader shad("Frag.glsl","Vert.glsl");
    Renderer::currentshader = shad;
    
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Renderer::Size_x / (float)Renderer::Size_y, 1.0f, -100000.0f);
    proj *= glm::lookAt(glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Renderer::currentshader.setmat4("projection", proj);

    
    std::vector<std::shared_ptr<Entity>> Entities;
    Entities.emplace_back(std::make_shared<ModelEntity>(path));
    Entities.emplace_back(std::make_shared<ModelEntity>(path));
   
    RenderBuffer RBO(Renderer::Size_x,Renderer::Size_y);
    
    while (!glfwWindowShouldClose(window))                                                                              
    {
    
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        
        proj = glm::perspective(glm::radians(45.0f), (float)(Renderer::Size_x*0.7) / (float)Renderer::Size_y, 1.0f, -100000.0f);
        proj *= glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        Renderer::currentshader.setmat4("projection", proj);
        
        
        Renderer::clear();
    
        Renderer::sync();
    
        RBO.Resize(Renderer::Size_x*0.7,Renderer::Size_y);
        RBO.bind();
        
        Renderer::clear();
        
        for (auto ent : Entities)
            ent->OnUpdate();
        
        RBO.unbind();
        
        
        GUI::doGUI(Entities,RBO); //will draw contents of FBO on a window & draw entities gui parts
        
        
        
        GUI::RenderGUI();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    std::cout << "closed" << std::endl;
    Renderer::sync();
    Renderer::shutdown();
    return 0;
}