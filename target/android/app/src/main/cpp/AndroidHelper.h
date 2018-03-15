#ifndef ANDROID_ANDROIDHELPER_H
#define ANDROID_ANDROIDHELPER_H

#include <jni.h>

class AndroidHelper{

public:
    static void setEnvAndAssetManager(JNIEnv *env, jobject assetManager);

    static char *openTextFile(const char *path);
};

#endif //ANDROID_ANDROIDHELPER_H
