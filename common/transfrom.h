#pragma once

#include <vector>
#include <iostream>
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <cstdarg>

using namespace glm;


class Transform {
	mat4 transform = mat4(1);

public:
	long vertexDataEnable = 1;

	Transform();
	virtual ~Transform();


	void SetTransformation(vec3 _pos, vec3 _rot, vec3 _scale);
	void Translate(vec3 _pos);
	void Rotate(vec3 _axis, float32 angle);
	void Scale(vec3 _scale);

	mat4 GetTransfrom();
	void ResetTransfrom();
};