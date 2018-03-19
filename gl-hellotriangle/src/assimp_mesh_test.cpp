#include <helper.h>
#include "assimp_mesh_test.h"
#include "shader.h"
#include "mesh.h"
#include "orbit_camera.h"
#include "glm\gtc\type_ptr.hpp"
#include "assimp_model.h"
#include "texture.h"

AssimpMeshTestApplication::AssimpMeshTestApplication()
{
}

AssimpMeshTestApplication::~AssimpMeshTestApplication()
{
}
Texture *textureTest = 0;
void AssimpMeshTestApplication::Init()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	textureTest = new Texture("res/textures/checks.png");
	camera = new OrbitCamera();

    shader = new Shader("res/shaders/simpletexture.vert", "res/shaders/simpletexture.frag");
    shader->Set();
	textureTest->Bind(0);
	//	shader->SetUniform("color", glm::value_ptr(vec3(1.0)));
	shader->SetUniform("Texture", (int *)textureTest->getHandle());

	prevTime = currentTimeInMS();

	assimpModel = new AssimpModel("res/models/box2.obj");
	assimpModel->getTransform()->SetTransformation(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(1.1f, 1.1f, 1.1f)
	);

	glEnable(GL_DEPTH_TEST);

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
	textureTest->Bind(0);
	mat4 mvp = perspectiveMatrix * viewMatrix * assimpModel->getTransform()->GetTransfrom();
	shader->SetUniform("mvp", glm::value_ptr(mvp));
	shader->SetUniform("Texture", 0);

	assimpModel->Render(camera);

}

void AssimpMeshTestApplication::ViewportChanged(int _width, int _height)
{
	Log("ViewportChanged %d %d", _width, _height);
	glViewport(0, 0, _width, _height);
	camera->ViewportChanged(_width, _height);
}
