#include <helper.h>
#include "assimp_mesh_test.h"
#include "shader.h"
#include "mesh.h"
#include "orbit_camera.h"
#include "glm\gtc\type_ptr.hpp"
#include "assimp_model.h"

AssimpMeshTestApplication::AssimpMeshTestApplication()
{
}

AssimpMeshTestApplication::~AssimpMeshTestApplication()
{
}
void AssimpMeshTestApplication::Init()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	camera = new OrbitCamera();

    shader = new Shader("res/shaders/simple_mvp.vert", "res/shaders/simple.frag");
    shader->Set();
	shader->SetUniform("color", glm::value_ptr(vec3(1.0)));

	prevTime = currentTimeInMS();

	assimpModel = new AssimpModel("res/models/nanosuit.obj");
	assimpModel->getTransform()->SetTransformation(
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.1f, 0.1f, 0.1f)
	);

}

void AssimpMeshTestApplication::Update()
{
}

void AssimpMeshTestApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	long deltaTime = currentTimeInMS() - prevTime;
	prevTime = currentTimeInMS();

	camera->Orbit(deltaTime * 0.01f);

	perspectiveMatrix = camera->GetPerspectiveMatrix();
	viewMatrix = camera->GetViewMatrix();

	shader->Set();
	mat4 mvp = perspectiveMatrix * viewMatrix * assimpModel->getTransform()->GetTransfrom();
	shader->SetUniform("mvp", glm::value_ptr(mvp));

	assimpModel->Render(camera);

}

void AssimpMeshTestApplication::ViewportChanged(int _width, int _height)
{
	Log("ViewportChanged %d %d", _width, _height);
	glViewport(0, 0, _width, _height);
	camera->ViewportChanged(_width, _height);
}
