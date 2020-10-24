#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"


class Camera
{
public:
	Camera() {};
	Camera(float fov,glm::vec3 target,glm::vec3 position);
	void bind();
	void unbind();
	glm::mat4 projection;
	glm::mat4 transform;
	bool bound;
private:
};