#pragma once
#include <string>
#include <vector>
#include <map>
#include "GLES3\gl3.h"

#define SHADER_RES_DIR	"shaders/"
#define SHADER_RESOURCE(x)		RESOURCES_PATH SHADER_RES_DIR GLSL_VERSION PATH_SEPRATER x


class Shader
{
	struct locationData {
		int loc;
		GLenum type; //data type
	};
	unsigned int programId = 0;
	unsigned int vertShaderId = 0;
	unsigned int fragShaderId = 0;

	std::map<std::string, int> attributeLocs;
	std::map<std::string, locationData> uniformLocs;

	unsigned int	CompileShaderCode(std::string _shaderCode, unsigned int _shaderType);
public:
	
	Shader();
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile);
	void InitAttributeUniformLocation();
	virtual ~Shader();

	void CompileShaderCode(std::string _shaderCodeVert, std::string _shaderCodeFrag);

	int GetUniformLocation(std::string _uniform);
	bool SetUniform(std::string _uniform, const GLfloat * value, int count=1);
	bool SetUniform(std::string _uniform, const GLint * value, int count=1);
	bool SetUniform(std::string _uniform, const GLint _value);
	int GetAttribLocation(std::string _attrib);
	void Set();
	void Reset();
};

