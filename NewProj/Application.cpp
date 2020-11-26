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

    RenderBuffer RBO(Renderer::Size_x, Renderer::Size_y);

    Camera camera(45.0f, glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f));
    std::shared_ptr<CameraEntity> cameraent = std::make_shared<CameraEntity>(camera);
    Entities.emplace_back(cameraent);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Renderer::clear();

        Renderer::sync();

        RBO.Resize(Renderer::Size_x * 0.7, Renderer::Size_y);


        RBO.bind();
        Renderer::clear();

        for (auto ent : Entities)
            ent->OnUpdate();

        RBO.unbind();


        GUI::doGUI(Entities, RBO); //will draw contents of FBO on a window & draw entities gui parts

        GUI::RenderGUI();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "closed" << std::endl;
    Renderer::sync();
    Renderer::shutdown();
    return 0;
};