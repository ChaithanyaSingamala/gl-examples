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