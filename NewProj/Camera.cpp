#include "Camera.h"


Camera::Camera(float fov, glm::vec3 target, glm::vec3 position)
{
	this->projection = glm::perspective(glm::radians(fov), (float)(Renderer::Size_x * 0.7) / (float)Renderer::Size_y, 1.0f, -100000.0f);
	this->transform = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::bind()
{
	
	Renderer::currentshader.setmat4("view", this->transform);
	Renderer::currentshader.setmat4("projection", this->projection);
}
