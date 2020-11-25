#include "Renderer.h"
std::mutex Renderer::lock;
std::vector<queueitem> Renderer::queue;
GLFWwindow* Renderer::window;
int Renderer::Size_x;
int Renderer::Size_y;

GLFWwindow* Renderer::init(int sizex,int sizey)
{
    Size_x = sizex;
    Size_y = sizey;
    if (!glfwInit())
        return nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(sizex, sizey, "ViewPort", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error with glew :c" << std::endl;
        std::cin;
        return nullptr;
    }
    glfwSwapInterval(1);
    Renderer::window = window;
    return window;
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::shutdown()
{
    glfwDestroyWindow(Renderer::window);
}

void Renderer::sync()
{
    std::lock_guard<std::mutex> lck(Renderer::lock);
    glfwGetWindowSize(window, &Renderer::Size_x, &Renderer::Size_y);
    glViewport(0, 0, Renderer::Size_x, Renderer::Size_y);
    if (queue.size() == 0) return;
	for (int i = 0; i < queue.size(); i++)
	{
		//do all the opengl shit to add a VAO etc...
		queueitem currentitem = queue[i];
        if(currentitem.Fn == deletemesh) removemesh(currentitem);
        if (currentitem.Fn == loadmesh) addmesh(currentitem);
        
	}
	queue.clear();
}

void Renderer::additem(queueitem item)
{
	//std::lock_guard<std::mutex> lck(Renderer::lock);
	queue.push_back(item);
    return;
}

void Renderer::DrawIndexed(unsigned int VAO, unsigned int numindicies)
{
    std::lock_guard<std::mutex> lck(Renderer::lock);

    if (VAO == 0) return;
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, numindicies, GL_UNSIGNED_INT, 0);
    
}



void Renderer::addmesh(queueitem item)
{
    queueitem currentitem = item;

    glGenVertexArrays(1, currentitem.VAO); //creates VAO at location

    glGenBuffers(1, currentitem.VBO); //creates another buffer
    glGenBuffers(1, currentitem.EBO); //creates buffer

    glBindVertexArray(*currentitem.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *currentitem.VBO);
    glBufferData(GL_ARRAY_BUFFER, currentitem.verticies.size() * sizeof(vertex), &currentitem.verticies[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *currentitem.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentitem.indices.size() * sizeof(unsigned int), &currentitem.indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
   // glDeleteBuffers(1, currentitem.VBO);
   // glDeleteBuffers(1, currentitem.EBO);
    glBindVertexArray(0);
}

void Renderer::removemesh(queueitem item)
{

    glDeleteBuffers(1, item.EBO);
    glDeleteBuffers(1, item.VBO);
    glDeleteVertexArrays(1, item.VAO);

    delete item.VAO;
    delete item.VBO;
    delete item.EBO;
}

