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
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#endif
#include "GLES3\gl3.h"
#include <vector>


//std::string ReadTextFile(std::string _filename)
//{
//#if ANDROID_BUILD
//	std::string output = AndroidHelper::openTextFile(_filename.c_str());
//#else
//	std::ifstream file(_filename);
//	if (!file.good())
//		LogE("fail to open file %s", _filename.c_str());
//
//	std::string output = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
//#endif
//	return output;
//}

std::vector<char> ReadBinaryFile(std::string filename)
{
#if ANDROID_BUILD
	return AndroidHelper::openFile(filename.c_str());
#else
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	if (!ifs.good())
		LogE("fail to open file %s", filename.c_str());

	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	result.push_back('\0');

	return result;
#endif
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

#ifdef _WIN32

// MSVC defines this in winsock2.h!?
typedef struct timeval {
	long tv_sec;
	long tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
	// until 00:00:00 January 1, 1970 
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	return 0;
}
#endif

void PrintAnyGLError()
{
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		

		std::string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		Log("OpenGL error: %x %s", err, error.c_str());

	}

}

long currentTimeInMS()
{
	struct timeval tv;
	gettimeofday(&tv, (struct timezone *) NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
