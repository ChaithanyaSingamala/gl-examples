#include "application.hpp"
#include "GLES3\gl3.h"
#include "glm\glm.hpp"

class Shader;
class Mesh;
class OrbitCamera;

using namespace glm;

class MeshTestApplication : public Application
{
	Shader *shader = 0;
	Mesh *testMesh = 0;
	OrbitCamera *camera;

	long prevTime;

	mat4 perspectiveMatrix;
	mat4 viewMatrix;
	vec3 light1Pos;
	vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void ViewportChanged(int _width, int _height) override;

	MeshTestApplication();
	virtual ~MeshTestApplication();
	Mesh * CreateNewModelCube(Shader * _shader);
};