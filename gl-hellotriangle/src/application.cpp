#include "application.h"
#include "GLES3\gl3.h"

Application::Application(Interface *_interface):appInterface(_interface)
{
}

Application::~Application()
{
}

void Triangle_UsingVBO_NoShader()
{
	static bool init = false;

	static GLuint vboId1 = 0;
	static GLuint vboId2 = 0;
	if (!init)
	{
		{

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
		}
		glBindBuffer(GL_ARRAY_BUFFER, vboId1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		if(1)
		{

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
		}
		glBindBuffer(GL_ARRAY_BUFFER, vboId2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		init = true;
	}

	//glBindBuffer(GL_ARRAY_BUFFER, vboId1);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBindBuffer(GL_ARRAY_BUFFER, vboId2);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	//glBindBuffer(GL_ARRAY_BUFFER, vboId1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(vaoId2);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId2);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Application::Init()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glViewport(0, 0, appInterface->Width(), appInterface->Height());


}

void Application::Update()
{
}

void Application::Render()
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Triangle_UsingVBO_NoShader();
	//Triangle_UsingVAO_NoShader();

}

void Application::ViewportChanged(int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}
