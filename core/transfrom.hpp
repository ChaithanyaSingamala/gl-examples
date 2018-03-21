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

	Transform() {}
	virtual ~Transform() {}


	void SetTransformation(vec3 _pos, vec3 _rot, vec3 _scale)
	{
		transform = mat4(1);

		transform = translate(transform, _pos);
		transform = rotate(transform, _rot.x, vec3(1.0, 0.0, 0.0));
		transform = rotate(transform, _rot.y, vec3(0.0, 1.0, 0.0));
		transform = rotate(transform, _rot.z, vec3(0.0, 0.0, 1.0));
		transform = scale(transform, vec3(_scale));

	}
	void Translate(vec3 _pos)
	{
		transform = translate(transform, _pos);
	}
	void Rotate(vec3 _axis, float32 angle)
	{
		transform = rotate(transform, angle, _axis);
	}
	void RotateX(float32 angle)
	{
		transform = rotate(transform, angle, vec3(1.0, 0.0, 0.0));
	}
	void RotateY(float32 angle)
	{
		transform = rotate(transform, angle, vec3(0.0, 1.0, 0.0));
	}
	void RotateZ(float32 angle)
	{
		transform = rotate(transform, angle, vec3(0.0, 0.0, 1.0));
	}
	void Scale(vec3 _scale)
	{
		transform = scale(transform, _scale);
	}
	void Scale(float _scale)
	{
		transform = scale(transform, vec3(_scale));
	}

	mat4 Get()
	{
		return transform;
	}
	void Reset()
	{
		transform = mat4(1);
	}
};