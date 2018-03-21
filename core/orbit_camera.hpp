#pragma once

#include "camera.hpp"

class OrbitCamera : public Camera
{
	glm::float32 fov = 43.0f;
	glm::float32 farPlane = 100.0f;
	glm::float32 nearPlane = 0.1f;

	glm::vec3 center = glm::vec3(0.0);

	glm::float32 orbitAngle = 90.0f;
	glm::float32 orbitDistance = 4.0f;
	glm::float32 orbitHeight = 1.0f;

	glm::mat4	viewMatrix;
	glm::mat4	projectionMatrix;

	int width = 800;
	int height = 600;

	void UpdateViewMatrix()
	{
		viewMatrix = glm::mat4(1);
		if (orbitAngle > 360.f)
			orbitAngle -= 360.f;
		glm::vec3 posOffset = glm::vec3(0.0f);
		posOffset.x = orbitDistance * cos(glm::radians(orbitAngle));
		posOffset.y = orbitHeight;
		posOffset.z = orbitDistance * sin(glm::radians(orbitAngle));
		//posOffset *= position;
		//std::cout << posOffset.x << "," << posOffset.z << std::endl;

		viewMatrix = glm::lookAt(posOffset, center, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	void UpdateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(glm::radians(fov), width / (float)height, nearPlane, farPlane);
		//projectionMatrix = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 1000.0f);
	}

public:
	OrbitCamera()
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix();
	}
	virtual ~OrbitCamera() {}

	virtual glm::mat4 GetPerspectiveMatrix() override
	{
		return projectionMatrix;
	}

	virtual glm::mat4 GetViewMatrix() override
	{
		return viewMatrix;
	}
	virtual void SetOrbitAngle(glm::float32 _angle)
	{
		orbitAngle = _angle;
	}
	virtual void SetOrbitDistance(glm::float32 _distance)
	{
		orbitDistance = _distance;
	}
	virtual void SetOrbitHeight(glm::float32 _height)
	{
		orbitHeight = _height;
	}
	virtual void SetOrbitCenter(glm::vec3 _center)
	{
		center = _center;
		UpdateViewMatrix();
	}

	virtual void Orbit(glm::float32 _speed)
	{
		orbitAngle += _speed;
		UpdateViewMatrix();
	}

	virtual void SetProjection(glm::float32 _fov = 0.0f, glm::float32 _near = 0.0f, glm::float32 _far = 0.0f, glm::float32 _width = 800, glm::float32 _height = 800)
	{
		if (_fov)
			fov = _fov;
		if (_near)
			nearPlane = _near;
		if (_far)
			farPlane = _far;
		if (_width)
			width = _width;
		if (_height)
			height = _height;

		UpdateProjectionMatrix();
	}

	virtual void ViewportChanged(glm::float32 _width = 800, glm::float32 _height = 800)
	{
		width = _width;
		height = _height;

		UpdateProjectionMatrix();
	}

};