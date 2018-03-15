#include "shader.h"
#include <iostream>
#include "helper.h"

//#define SHADER_CHECK_STATUS	1

#ifdef SHADER_CHECK_STATUS
bool CheckStatus(unsigned int objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
#endif

Shader::Shader()
{

}

//Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile, ShaderAttribInfo _vertexAttributeLocs)
//{
//	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
//	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);
//
//	CompileShaderCode(vertShaderCode, fragShaderCode);
//	InitAttribLocations(_vertexAttributeLocs);
//}

Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile)
{
	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);

	CompileShaderCode(vertShaderCode, fragShaderCode);

	InitAttributeUniformLocation();

}

void Shader::InitAttributeUniformLocation()
{
	int count = 0;
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)
	const GLsizei bufSize = 32; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &count);
	printf("Active Attributes: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		glGetActiveAttrib(programId, (GLuint)i, bufSize, &length, &size, &type, name);
		attributeLocs[name] = glGetAttribLocation(programId, name);
		//LogI("Attribute #%d Type: %u Name: %s\n", i, type, name);
	}

	glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		glGetActiveUniform(programId, (GLuint)i, bufSize, &length, &size, &type, name);
		uniformLocs[name] = glGetUniformLocation(programId, name);
		//LogI("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}
}

void Shader::CompileShaderCode(std::string _shaderCodeVert, std::string _shaderCodeFrag)
{
	vertShaderId = CompileShaderCode(_shaderCodeVert, GL_VERTEX_SHADER);
	fragShaderId = CompileShaderCode(_shaderCodeFrag, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);

	glLinkProgram(programId);

#ifdef SHADER_CHECK_STATUS
	CheckStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
#endif
}

Shader::~Shader()
{
	Reset();
	glDetachShader(programId, vertShaderId);
	glDetachShader(programId, fragShaderId);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);
	glDeleteProgram(programId);
	programId = 0;
	vertShaderId = 0;
	fragShaderId = 0;
}

int Shader::GetUniformLocation(std::string _uniform)
{
	if (uniformLocs.find(_uniform) == uniformLocs.end())
	{//not found
		return -1;
	}
	else
	{
		return uniformLocs[_uniform];
	}
	return 0;
}

int Shader::GetAttribLocation(std::string _attrib)
{
//	return attrribLocations[_attrib];
	if (attributeLocs.find(_attrib) == attributeLocs.end())
	{//not found
		return -1;
	}
	else
	{
		return attributeLocs[_attrib];
	}
	return 0;
	return 0;
}

void Shader::Set()
{
	glUseProgram(programId);
}

void Shader::Reset()
{
	glUseProgram(0);
}

#ifdef SHADER_CHECK_STATUS
bool CheckStatus(unsigned int objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType)
{
	int status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		int infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		Log("Info: ", "%s", buffer);
		ASSERT("failed in compile shader");
		delete[] buffer;
		return false;
	}
	return true;
}
#endif
unsigned int Shader::CompileShaderCode(std::string _shaderCode, unsigned int _shaderType)
{
	unsigned int shaderId = glCreateShader(_shaderType);
	const GLchar* code[1] = { _shaderCode.c_str() };
	glShaderSource(shaderId, 1, code, 0);
	glCompileShader(shaderId);

#ifdef SHADER_CHECK_STATUS
	CheckStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
#endif

	return shaderId;
}