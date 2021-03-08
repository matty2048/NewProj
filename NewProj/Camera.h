#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"


class Camera
{
public:
	Camera():projection(glm::mat4(1.0)),transform(glm::mat4(1.0)),bound(false) {};
	Camera(float fov,glm::vec3 target,glm::vec3 position);
	void Bind();
	void UnBind();
	glm::mat4 projection;
	glm::mat4 transform;
	bool bound;

};