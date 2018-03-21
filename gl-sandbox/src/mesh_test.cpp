#include <helper.h>
#include "mesh_test.h"
#include "shader.hpp"
#include "mesh.hpp"
#include "orbit_camera.hpp"
#include "glm\gtc\type_ptr.hpp"

MeshTestApplication::MeshTestApplication()
{
}

MeshTestApplication::~MeshTestApplication()
{
}

Mesh * MeshTestApplication::CreateNewModelCube(Shader *_shader)
{
	Mesh *mesh = 0;

	std::vector<GLfloat> vertexArray =
	{
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,							0.0f, 0.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,
		+0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 0.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		-0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,

		-0.5f, +0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		-0.5f,  0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		+0.5f, +0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,

		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f

	};
	std::vector<GLushort> indices;
	for (int i = 0; i < 36; i++)
	{
		indices.push_back(36 - i - 1);
	}



	mesh = new Mesh(vertexArray, indices, 
		{
			{ _shader->GetAttribLocation("vertexPosition"), 0, 3, 8 },
		//	{ _shader->GetAttribLocation("vertexColor"), 0, 3, 8 },/*temply use position as color value*/
		//	{ _shader->GetAttribLocation("vertexNormal"), 3, 3, 8, },
		//	{ _shader->GetAttribLocation("UV0"), 6, 2, 8 },
		}
	);

	return mesh;
}

void MeshTestApplication::Init()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	camera = new OrbitCamera();

    shader = new Shader("res/shaders/simple.vert", "res/shaders/simple.frag");
    shader->Set();
	shader->SetUniform("color", glm::value_ptr(vec3(1.0)));

	testMesh = CreateNewModelCube(shader);

	prevTime = currentTimeInMS();

}

void MeshTestApplication::Update()
{
}

void MeshTestApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	long deltaTime = currentTimeInMS() - prevTime;
	prevTime = currentTimeInMS();

	camera->Orbit(deltaTime * 0.01f);

	perspectiveMatrix = camera->GetPerspectiveMatrix();
	viewMatrix = camera->GetViewMatrix();

	shader->Set();
	mat4 mvp = perspectiveMatrix * viewMatrix * testMesh->getTransform()->Get();
	//shader->SetUniform("mvp", glm::value_ptr(mvp));

#if 0
	{
		static float rot = 0.0;
		rot += 0.001f * deltaTime;
		shader->Set();
		glUniformMatrix4fv(shader->GetUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
		glUniformMatrix4fv(shader->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

		testMesh->getTransform()->ResetTransfrom();
		testMesh->getTransform()->Rotate(glm::vec3(0.0, 1.0, 0.0), rot);
		testMesh->getTransform()->Translate(lightPos);
		testMesh->getTransform()->Scale(glm::vec3(0.1f));
		glm::mat4 m = testMesh->getTransform()->GetTransfrom();
		light1Pos.x = m[3][0];
		light1Pos.y = m[3][1];
		light1Pos.z = m[3][2];
		glm::mat3 normalMat = testMesh->getTransform()->GetTransfrom();
		normalMat = glm::inverse(normalMat);
		normalMat = glm::transpose(normalMat);
		glUniformMatrix3fv(shader->GetUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMat));
		glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testModelLightSource->GetTransfrom()));

		testModelLightSource->Render();
		shaderForLightSource->Reset();
	}
#endif
	
	testMesh->Render();

}

void MeshTestApplication::ViewportChanged(int _width, int _height)
{
    Log("ViewportChanged %d %d", _width, _height);
	glViewport(0, 0, _width, _height);
	camera->ViewportChanged(_width, _height);
}
