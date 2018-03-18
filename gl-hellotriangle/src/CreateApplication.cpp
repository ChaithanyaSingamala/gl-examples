#include <helper.h>
#include "hellotriangle.h"
#include "mesh_test.h"
#include "assimp_mesh_test.h"


Application *createApplication() {
	//return new HelloTriangleApplication();
	//return new MeshTestApplication();
	return new AssimpMeshTestApplication();
}
