#include "shader.h"
#include <iostream>
#include "helper.h"

#ifdef _WIN32
	#define SHADER_CHECK_STATUS	1
#endif

#ifdef SHADER_CHECK_STATUS
bool CheckStatus(unsigned int objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
#endif

Shader::Shader()
{

}

//Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile, ShaderAttribInfo _vertexAttributeLocs)
//{
//	std::string vertShaderCode = ReadTextFile(_vertexShaderFile);
//	std::string fragShaderCode = ReadTextFile(_fragmentShaderFile);
//
//	CompileShaderCode(vertShaderCode, fragShaderCode);
//	InitAttribLocations(_vertexAttributeLocs);
//}

Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile)
{
	std::vector<char> vertShaderCode = ReadBinaryFile(_vertexShaderFile);
	std::vector<char> fragShaderCode = ReadBinaryFile(_fragmentShaderFile);

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
		LogI("Attribute #%d Type: %u Name: %s location: %d", i, type, name, attributeLocs[name]);
	}

	glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		glGetActiveUniform(programId, (GLuint)i, bufSize, &length, &size, &type, name);
		uniformLocs[name] = { glGetUniformLocation(programId, name), type};
		LogI("Uniform #%d Type: %u Name: %s location: %d", i, type, name, uniformLocs[name]);
	}
}

void Shader::CompileShaderCode(std::vector<char> _shaderCodeVert, std::vector<char> _shaderCodeFrag)
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
		return uniformLocs[_uniform].loc;
	}
	return 0;
}

bool Shader::SetUniform(std::string _uniform, const GLfloat *value, int count)
{//will return false when uniform not found or when uniform type not supported
	if (uniformLocs.find(_uniform) == uniformLocs.end())
	{//not found
		return false; //not set
	}
	else
	{
		int location = uniformLocs[_uniform].loc;
		switch (uniformLocs[_uniform].type) {
		case GL_FLOAT:				glUniform1fv(location, count, value);				break;
		case GL_FLOAT_VEC2:			glUniform2fv(location, count, value);				break;
		case GL_FLOAT_VEC3:			glUniform3fv(location, count, value);				break;
		case GL_FLOAT_VEC4:			glUniform4fv(location, count, value);				break;
		case GL_FLOAT_MAT2:			glUniformMatrix2fv(location, count, GL_FALSE, value);				break;
		case GL_FLOAT_MAT3:			glUniformMatrix3fv(location, count, GL_FALSE, value);				break;
		case GL_FLOAT_MAT4:			glUniformMatrix4fv(location, count, GL_FALSE, value);				break;

		}

	}
	return false; //not supported 
}

bool Shader::SetUniform(std::string _uniform, const GLint *value, int count)
{//will return false when uniform not found or when uniform type not supported
	if (uniformLocs.find(_uniform) == uniformLocs.end())
	{//not found
		return false; //not set
	}
	else
	{
		int location = uniformLocs[_uniform].loc;
		switch (uniformLocs[_uniform].type) {
		case GL_INT:				glUniform1iv(location, count, value);				break;
		case GL_INT_VEC2:			glUniform2iv(location, count, value);				break;
		case GL_INT_VEC3:			glUniform3iv(location, count, value);				break;
		case GL_INT_VEC4:			glUniform4iv(location, count, value);				break;
		case GL_SAMPLER_2D:			glUniform1i(location, *value);						break;

		}

	}
	return false; //not supported 
}

bool Shader::SetUniform(std::string _uniform, const GLint _value)
{//will return false when uniform not found or when uniform type not supported
	if (uniformLocs.find(_uniform) == uniformLocs.end())
	{//not found
		return false; //not set
	}
	else
	{
		int location = uniformLocs[_uniform].loc;
		switch (uniformLocs[_uniform].type) {
		case GL_INT:				glUniform1i(location, _value);				break;
		case GL_SAMPLER_2D:			glUniform1i(location, _value);				break;

		}

	}
	return false; //not supported 
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
		Log("%s", buffer);
		LogE("failed in compile shader");
		delete[] buffer;
		return false;
	}
	return true;
}
#endif
unsigned int Shader::CompileShaderCode(std::vector<char> _shaderCode, unsigned int _shaderType)
{
	unsigned int shaderId = glCreateShader(_shaderType);
	const GLchar* code[1] = { _shaderCode.data() };
	glShaderSource(shaderId, 1, code, 0);
	glCompileShader(shaderId);

#ifdef SHADER_CHECK_STATUS
	CheckStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
#endif

	return shaderId;
}