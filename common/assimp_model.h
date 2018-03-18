#pragma once

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


using namespace glm;
class Transform;



class AssimpModel : public Model {

public:
	AssimpModel(std::string _filename);
	void ProcessNode(aiNode * node, const aiScene * scene);
	Mesh * ProcessMesh(aiMesh * mesh, const aiScene * scene);

	virtual void Render(Camera *camera) override;
};