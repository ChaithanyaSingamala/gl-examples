#pragma once

#include "mesh.hpp"


using namespace glm;
class Transform;
class Camera;

class Scene {
protected:
	std::vector<Mesh*> meshes;
	Transform transform;

public:
	Scene() {

	}

	virtual void Render(Camera *camera) {}

	virtual Transform* getTransform() { return &transform; }

};