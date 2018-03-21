#pragma once

#include "scene.hpp"


#include "transfrom.hpp"
#include "helper.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using namespace glm;
using namespace std;


class AssimpScene : public Scene {

public:
	AssimpScene(std::string _filename) 
	{
		vector<char> dataStr = ReadBinaryFile(_filename);
		size_t dataLength = dataStr.size();
		void* data = dataStr.data();

		string ext = _filename.substr(_filename.find_last_of('.'), _filename.length());

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFileFromMemory(data, dataLength, aiProcess_Triangulate | aiProcess_FlipUVs, ext.c_str());
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			string error = importer.GetErrorString();
			LogE("ERROR::ASSIMP: %s", error.c_str());
		}
		string directory = _filename.substr(0, _filename.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);

	}
	void ProcessNode(aiNode * node, const aiScene * scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}

	}
	Mesh * ProcessMesh(aiMesh * mesh, const aiScene * scene)
	{
		std::vector<unsigned short> indices;
		//vector<Texture> textures;

		int totalVertexLength = 8;
		std::vector<float> vertices(mesh->mNumVertices * totalVertexLength);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertices[0 + i * totalVertexLength] = mesh->mVertices[i].x;
			vertices[1 + i * totalVertexLength] = mesh->mVertices[i].y;
			vertices[2 + i * totalVertexLength] = mesh->mVertices[i].z;
			// Normals
			if (mesh->mNormals)
			{
				vertices[3 + i * totalVertexLength] = mesh->mNormals[i].x;
				vertices[4 + i * totalVertexLength] = mesh->mNormals[i].y;
				vertices[5 + i * totalVertexLength] = mesh->mNormals[i].z;
			}
			else
			{
				vertices[3 + i * totalVertexLength] = 0.0f;
				vertices[4 + i * totalVertexLength] = 0.0f;
				vertices[5 + i * totalVertexLength] = 0.0f;
			}

			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				vertices[6 + i * totalVertexLength] = mesh->mTextureCoords[0][i].x;
				vertices[7 + i * totalVertexLength] = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				vertices[6 + i * totalVertexLength] = 0.0f;
				vertices[7 + i * totalVertexLength] = 0.0f;
			}
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		/** /
		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		*/
		return new Mesh(vertices, indices,
		{
			{ 0, 0, 3, 8 },
			{ 2, 3, 3, 8, },
			{ 1, 6, 2, 8 },
		}
		);
#if 0
		return new Mesh(vertices, indices,
		{
			{ _shader->GetAttribLocation("vertexPosition"), 0, 3, 8 },
			{ _shader->GetAttribLocation("vertexNormal"), 3, 3, 8, },
			{ _shader->GetAttribLocation("UV0"), 6, 2, 8 },
		}
		);
#endif
	}

	virtual void Render(Camera *camera) override
	{
		for (auto mesh : meshes)
			mesh->Render();
	}
};