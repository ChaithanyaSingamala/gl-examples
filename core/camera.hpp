#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

class Camera
{
public:
	virtual mat4 GetPerspectiveMatrix() = 0;

	virtual mat4 GetViewMatrix() = 0;

	virtual void ViewportChanged(glm::float32 _width = 800, glm::float32 _height = 800) = 0;

};