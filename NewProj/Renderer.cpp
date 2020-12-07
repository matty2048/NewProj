#include "Renderer.h"
std::mutex Renderer::lock;
std::vector<queueitem> Renderer::queue;
GLFWwindow* Renderer::window;
int Renderer::Size_x;
int Renderer::Size_y;


GLFWwindow* Renderer::init(int sizex,int sizey) //initializes the renderer
{
    Size_x = sizex;
    Size_y = sizey;
    if (!glfwInit())
        return nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  //initializes GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(sizex, sizey, "ViewPort", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }
    //Creates GLFW window for drawing to
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) ///initializes glew
    {
        std::cout << "error with glew :c" << std::endl;
        std::cin;
        return nullptr;
    }
    
    glfwSwapInterval(1); 
    Renderer::window = window;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);       //enables glError + binds message callback on error
    glDebugMessageCallback(Renderer::MessageCallback, 0);

    return window;
}

//<NOT MY COODE!!!>
void GLAPIENTRY Renderer::MessageCallback(GLenum source,
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
//</NOT MY CODE!!!>


void Renderer::clear() ///clears the currently bound renderbuffers colour + depth
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::shutdown()
{
    glfwDestroyWindow(Renderer::window);
}

void Renderer::sync() //synchronizes the model loading
{
    std::lock_guard<std::mutex> lck(Renderer::lock); //gets the resource lock to avoid collisions
    glfwGetWindowSize(window, &Renderer::Size_x, &Renderer::Size_y);
    glViewport(0, 0, Renderer::Size_x, Renderer::Size_y);
    if (queue.size() == 0) return;
	for (int i = 0; i < queue.size(); i++) //loops over meshes in queue 
	{
		queueitem currentitem = queue[i]; 
        if(currentitem.Fn == deletemesh) removemesh(currentitem); //removes a mesh from GPU memory
        if (currentitem.Fn == loadmesh) addmesh(currentitem);     //adds a mesh to GPU
        
	}
	queue.clear(); //clears the queue
    //this could cause minor hitches if lots of meshes finish proccessing on the same frame could spread load over
    //multiple frames but rather pointless in this use case
}

void Renderer::additem(queueitem item)
//adds item to queue
{
	
	queue.push_back(item); 
    return;
}

void Renderer::DrawIndexed(unsigned int VAO, unsigned int numindicies) 
//draws an indexed mesh
{
    std::lock_guard<std::mutex> lck(Renderer::lock); //locks so that can't be drawn while loading 
    if (VAO == 0) return; //makes sure a VAO exists 
    glBindVertexArray(VAO); //binds the meshes VAO
    glDrawElements(GL_TRIANGLES, numindicies, GL_UNSIGNED_INT, 0); //draws  the mesh
    
}



void Renderer::addmesh(queueitem item)
{
    queueitem currentitem = item;

    glGenVertexArrays(1, currentitem.VAO); //creates vertex array at location

    glGenBuffers(1, currentitem.VBO); //creates vertex buffer
    glGenBuffers(1, currentitem.EBO); //creates index buffer

    glBindVertexArray(*currentitem.VAO); //binds the  VAO
    glBindBuffer(GL_ARRAY_BUFFER, *currentitem.VBO); //binds vertex buffer to the VAO
    glBufferData(GL_ARRAY_BUFFER, currentitem.verticies.size() * sizeof(vertex), &currentitem.verticies[0], GL_STATIC_DRAW);
    //adds the data to the vertex buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *currentitem.EBO); //binds the index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentitem.indices.size() * sizeof(unsigned int), &currentitem.indices[0], GL_STATIC_DRAW);
    //adds the index data to the index buffer

    glEnableVertexAttribArray(0); //enables the position element of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0); //sets how large the first component of the 
    //vertex data is 

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

    glBindVertexArray(0); //unbinds the vertex array
}

void Renderer::removemesh(queueitem item)
{
    std::cout << "mesh removed" << std::endl;
    glDeleteBuffers(1, item.EBO);
    glDeleteBuffers(1, item.VBO);
    glDeleteVertexArrays(1, item.VAO);

    delete item.VAO;
    delete item.VBO;
    delete item.EBO;
}

