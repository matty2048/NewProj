#include "Camera.h"


Camera::Camera(float fov, glm::vec3 target, glm::vec3 position) //  default camera constructor
{
	this->projection = glm::perspective(glm::radians(fov), (float)(Renderer::Size_x * 0.7) / (float)Renderer::Size_y, 1.0f, -100000.0f);

	this->transform = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Bind() //sets the current shaders view and projection matricies to this
{
	
	Renderer::currentshader.SetMat4("view", this->transform); 
	Renderer::currentshader.SetMat4("projection", this->projection);
}
