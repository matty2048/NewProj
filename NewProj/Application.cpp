#include "Renderer.h"
#include <iostream>
#include "RenderBuffer.h"
#include "GUI.h"
#include <memory>

 // TODO: I dont like the camera controller
int main()
{

    GLFWwindow* window = Renderer::init(1024, 1024);     //
    if (window == nullptr)                               //
    {                                                    // initializing window & 
        return -1;                                       // creating opengl context
    }                                                    //
    GUI::init(window);                                   //
   
  

    Shader shad("Frag.glsl", "Vert.glsl");  //
    Renderer::currentshader = shad;         //adds the default shader
    
    const char* path = "arch.obj";                               //
    std::vector<std::shared_ptr<Entity>> Entities;               //
    Entities.emplace_back(std::make_shared<ModelEntity>(path));  // Creates the entity storage & adds two test models
    Entities.emplace_back(std::make_shared<ModelEntity>(path));  //
   
    RenderBuffer RBO(Renderer::Size_x,Renderer::Size_y);        //creates the render buffer for the viewport
    
    Camera camera(45.0f,glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f));                     //
    std::shared_ptr<CameraEntity> cameraent =  std::make_shared<CameraEntity>(camera);      //
    Entities.emplace_back(cameraent);                                                       //adds a default camera
    glEnable(GL_DEPTH_TEST); //enables depth testing
   
    while (!glfwWindowShouldClose(window))                                                                              
    {
    
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        
        Renderer::clear(); //clears the default framebuffer
    
        Renderer::sync(); //handles the synchronization for model loading
    
        RBO.Bind(); //binds the render buffer for drawing in the viewport
        RBO.Resize(Renderer::Size_x*0.7,Renderer::Size_y);
        
        Renderer::clear();
        
        for (auto ent : Entities)              
            ent->OnUpdate();
        
        RBO.UnBind(); //unbinds the render buffer so default render buffer is used
        
        
        GUI::DoGUI(Entities,RBO); //will draw contents of RBO.FBO on a window & draw entities gui parts
        
        
        GUI::RenderGUI(); //renders the GUI 

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    std::cout << "closed" << std::endl;
    Renderer::sync();
    Renderer::shutdown();
    return 0;
};