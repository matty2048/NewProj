#include "Renderer.h"
#include <iostream>
#include "RenderBuffer.h"
#include "GUI.h"
#include <memory>


int main()
{

    GLFWwindow* window = Renderer::init(1024, 1024);
    if (window == nullptr)
    {
        return -1;
    }
    GUI::init(window);
   
  
    const char* path = "arch.obj";

    Shader shad("Frag.glsl", "Vert.glsl");
    Renderer::currentshader = shad;
    
    std::vector<std::shared_ptr<Entity>> Entities;
    Entities.emplace_back(std::make_shared<ModelEntity>(path));
    Entities.emplace_back(std::make_shared<ModelEntity>(path));
   
    RenderBuffer RBO(Renderer::Size_x,Renderer::Size_y);
    
    Camera camera(45.0f,glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f));
    std::shared_ptr<CameraEntity> cameraent =  std::make_shared<CameraEntity>(camera);
    Entities.emplace_back(cameraent); //adds a default camera
    glEnable(GL_DEPTH_TEST); //enables depth testing
    // TODO: I dont like the camera controller
    while (!glfwWindowShouldClose(window))                                                                              
    {
    
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        
        Renderer::clear(); //clears the default framebuffer
    
        Renderer::sync(); //handles the synchronization for model loading
    
        RBO.bind(); //binds the render buffer for drawing in the viewport
        RBO.Resize(Renderer::Size_x*0.7,Renderer::Size_y);
        
        Renderer::clear();
        
        for (auto ent : Entities)              
            ent->OnUpdate();
        
        RBO.unbind(); //unbinds the render buffer so default render buffer is used
        
        
        GUI::doGUI(Entities,RBO); //will draw contents of RBO.FBO on a window & draw entities gui parts
        
        
        GUI::RenderGUI();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    std::cout << "closed" << std::endl;
    Renderer::sync();
    Renderer::shutdown();
    return 0;
};