#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#include <memory>
#include <iostream>
#include <mutex>
#include <vector>
//#include "Mesh.h"
struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};
enum functodo
{
	loadmesh, deletemesh
};
struct queueitem
{	//this is so garbage 
	functodo Fn;
	unsigned int* VAO;
	unsigned int* VBO;   
	unsigned int* EBO;
	std::vector<vertex> verticies;
	std::vector<unsigned int> indices;
};



class Renderer //static class which contains lots of rendering functions + window data
{
public:
	static int Size_x; //size of window NOT of internal window
	static int Size_y; //size of window NOT of internal window
	
	static GLFWwindow* init(int sizex,int sizey); //creates the first window
	static void clear(); //clears the currently bound framebuffer
	static void shutdown();
	
	static Shader currentshader;
	
	static void additem(queueitem item);
	static void sync();
	
	static void GLAPIENTRY MessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);

	static void DrawIndexed(unsigned int VAO,unsigned int numindicies); //draws in indexed mode//
	
	static std::mutex lock;
	
private:
	static void addmesh(queueitem item);
	static void removemesh(queueitem item);
	static GLFWwindow* window;
	static std::vector<queueitem> queue;
};