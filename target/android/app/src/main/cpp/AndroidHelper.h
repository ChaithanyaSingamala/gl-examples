#ifndef ANDROID_ANDROIDHELPER_H
#define ANDROID_ANDROIDHELPER_H

#include <jni.h>
#include <vector>

class AndroidHelper{

public:
    static void setEnvAndAssetManager(JNIEnv *env, jobject assetManager);

    static char *openTextFile(const char *path);

	static std::vector<char> openFile(const char *path);

};

#endif //ANDROID_ANDROIDHELPER_H
