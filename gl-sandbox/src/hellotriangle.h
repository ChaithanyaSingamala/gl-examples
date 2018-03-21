#include "application.h"
#include "GLES3\gl3.h"

class Shader;
class Mesh;

class HelloTriangleApplication : public Application
{
	bool init = false;
	GLuint vaoId1 = 0;
	GLuint vaoId2 = 0;
	GLuint vboId1 = 0;
	GLuint vboId2 = 0;
	Shader *shader = 0;
	Mesh *testMesh = 0;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void ViewportChanged(int _width, int _height) override;

	HelloTriangleApplication();
	virtual ~HelloTriangleApplication();
};