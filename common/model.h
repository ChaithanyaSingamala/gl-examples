#pragma once

#include "mesh.h"


using namespace glm;
class Transform;
class Camera;

class Model {
protected:
	std::vector<Mesh*> meshes;
	Transform transform;

public:
	Model() {

	}

	virtual void Render(Camera *camera);

	virtual Transform* getTransform() { return &transform; }

};