#include <helper.h>
#include "assimp_mesh_test.h"
#include "shader.hpp"
#include "mesh.hpp"
#include "orbit_camera.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "assimp_scene.hpp"
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	textureTest = new Texture("res/models/L200-OBJ/truck_color.jpg");
	camera = new OrbitCamera();
	camera->SetProjection(43.0f, 1.0f, 6.0f, 0, 0);

    shader = new Shader("res/shaders/lighting01.vert", "res/shaders/lighting01.frag");
    shader->Set();
	textureTest->Bind(0);
	//	shader->SetUniform("color", glm::value_ptr(vec3(1.0)));
	shader->SetUniform("Texture", (int *)textureTest->getHandle());

	prevTime = currentTimeInMS();

	assimpModel = new AssimpScene("res/models/L200-OBJ/L200-OBJ.obj");
	assimpModel->getTransform()->SetTransformation(
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.05f, 0.05f, 0.05f)
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
	mat4 mvp = perspectiveMatrix * viewMatrix * assimpModel->getTransform()->Get();
	shader->SetUniform("mvp", glm::value_ptr(mvp));
	shader->SetUniform("model", glm::value_ptr(assimpModel->getTransform()->Get()));
	shader->SetUniform("Texture", 0);
	glm::mat3 normalMat = assimpModel->getTransform()->Get();
	normalMat = glm::inverse(normalMat);
	normalMat = glm::transpose(normalMat);
	shader->SetUniform("normalMatrix", glm::value_ptr(normalMat));

	assimpModel->Render(camera);

}

void AssimpMeshTestApplication::ViewportChanged(int _width, int _height)
{
	Log("ViewportChanged %d %d", _width, _height);
	glViewport(0, 0, _width, _height);
	camera->ViewportChanged(_width, _height);
}
