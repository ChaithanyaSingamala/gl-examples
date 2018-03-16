#include "helper.h"
#include <cstdarg>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <assert.h>
#if ANDROID_BUILD
#include "AndroidHelper.h"
#endif
#include "GLES3\gl3.h"


std::string ReadFromFile(std::string _filename)
{
#if ANDROID_BUILD
	std::string output = AndroidHelper::openTextFile(_filename.c_str());
#else
	std::ifstream file(_filename);
	if (!file.good())
		LogE("fail to open file %s", _filename.c_str());

	std::string output = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
#endif
	return output;
}

void PrintOGLESInfo(bool printExtensions)
{
	Log("GL Version %s", (const char *)glGetString(GL_VERSION));
	Log("GL Vendor %s", (const char *)glGetString(GL_VENDOR));
	Log("GL Renderer %s", (const char *)glGetString(GL_RENDERER));
	Log("GLSL version %s", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
	if(printExtensions)
		Log("GL Extensions %s", (const char *)glGetString(GL_EXTENSIONS));
}
