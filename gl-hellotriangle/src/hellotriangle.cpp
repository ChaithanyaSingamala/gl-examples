#include <helper.h>
#include "hellotriangle.h"
#include "shader.h"
#include "mesh.h"

HelloTriangleApplication::HelloTriangleApplication()
{
}

HelloTriangleApplication::~HelloTriangleApplication()
{
}

Mesh * CreateNewModelCube(Shader *_shader)
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

	mesh = new Mesh(vertexArray, indices, 3,
		_shader->GetAttribLocation("vertexPosition"), 0, 3, 8,
		_shader->GetAttribLocation("vertexNormal"), 3, 3, 8,
		_shader->GetAttribLocation("UV0"), 6, 2, 8);

	return mesh;
}

void Triangle_UsingVAO_NoShader()
{
	static bool init = false;
	static GLuint vaoId1 = 0; 
	static GLuint vaoId2 = 0;

	static GLuint vboId1 = 0;
	static GLuint vboId2 = 0;
	if (!init)
	{
		{
			glGenVertexArrays(1, &vaoId1);
			glBindVertexArray(vaoId1);

			glGenBuffers(1, &vboId1);
			glBindBuffer(GL_ARRAY_BUFFER, vboId1);

			GLfloat z_value = 0.5f;
			std::vector<GLfloat> vertexArray =
			{
				+0.0f, +1.0f, z_value,
				+1.0f, +0.0f, z_value,
				-1.0f, +0.0f, z_value,
			};
			glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		if (1)
		{
			glGenVertexArrays(1, &vaoId2);
			glBindVertexArray(vaoId2);

			glGenBuffers(1, &vboId2);
			glBindBuffer(GL_ARRAY_BUFFER, vboId2);

			GLfloat z_value = 0.5f;
			std::vector<GLfloat> vertexArray =
			{
				+0.0f, +0.0f, z_value,
				+1.0f, -1.0f, z_value,
				-1.0f, -1.0f, z_value,
			};
			glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		init = true;
	}
	glBindVertexArray(vaoId1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(vaoId2);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);

}

void HelloTriangleApplication::Init()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    int posAttributeLoc = -1;
    int colorAttributeLoc = -1;
	if(1)
    {
        shader = new Shader("res/shaders/simple.vert", "res/shaders/simple.frag");
        shader->Set();
        posAttributeLoc = shader->GetAttribLocation("vertexPosition");
        colorAttributeLoc = shader->GetAttribLocation("vertexColor");

    }
	if(1)
    {
        glGenVertexArrays(1, &vaoId1);
        glBindVertexArray(vaoId1);

        glGenBuffers(1, &vboId1);
        glBindBuffer(GL_ARRAY_BUFFER, vboId1);

        GLfloat z_value = 0.5f;
        std::vector<GLfloat> vertexArray =
                {
                        +0.0f, +1.0f, z_value, 1.0, 0.0, 0.0,
                        +1.0f, +0.0f, z_value, 1.0, 0.0, 1.0,
                        -1.0f, +0.0f, z_value, 0.0, 1.0, 0.0,
                };
        glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

        //position
        glEnableVertexAttribArray(posAttributeLoc);
        glVertexAttribPointer(posAttributeLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);



#if 0
        //color based on position - testing
			glEnableVertexAttribArray(colorAttributeLoc);
			glVertexAttribPointer(colorAttributeLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
#else
        glEnableVertexAttribArray(colorAttributeLoc);
        glVertexAttribPointer(colorAttributeLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(float)));
#endif
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    if (1)
    {
        glGenVertexArrays(1, &vaoId2);
        glBindVertexArray(vaoId2);

        glGenBuffers(1, &vboId2);
        glBindBuffer(GL_ARRAY_BUFFER, vboId2);

        GLfloat z_value = 0.5f;
        std::vector<GLfloat> vertexArray =
                {
                        +0.0f, +0.0f, z_value,
                        +1.0f, -1.0f, z_value,
                        -1.0f, -1.0f, z_value,
                };
        glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(posAttributeLoc);
        glVertexAttribPointer(posAttributeLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        //color based on position - testing
        glEnableVertexAttribArray(colorAttributeLoc);
        glVertexAttribPointer(colorAttributeLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

	testMesh = CreateNewModelCube(shader);

}

void HelloTriangleApplication::Update()
{
}

void HelloTriangleApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Set();

    glBindVertexArray(vaoId1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(vaoId2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

	testMesh->Render();

}

void HelloTriangleApplication::ViewportChanged(int _width, int _height)
{
    Log("ViewportChanged %d %d", _width, _height);
	glViewport(0, 0, _width, _height);
}
