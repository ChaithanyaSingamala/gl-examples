#include "AndroidHelper.h"
#include <android/asset_manager_jni.h>
#include <android/log.h>

#define LOG_TAG "Lesson"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

static JNIEnv *sEnv = NULL;
static jobject sAssetManager = NULL;

static AAsset *loadAsset(const char *path) {
    AAssetManager *nativeManager = AAssetManager_fromJava(sEnv, sAssetManager);
    if (nativeManager == NULL) {
        return NULL;
    }
    return AAssetManager_open(nativeManager, path, AASSET_MODE_UNKNOWN);
}
void AndroidHelper::setEnvAndAssetManager(JNIEnv *env, jobject assetManager) {
    sEnv = env;
    sAssetManager = assetManager;
}

char *AndroidHelper::openTextFile(const char *path) {
    AAsset *asset = loadAsset(path);
    if (asset == NULL) {
        LOGE("Couldn't load %s", path);
        return NULL;
    }
    off_t length = AAsset_getLength(asset);
    char *buffer = new char[length + 1];
    int num = AAsset_read(asset, buffer, length);
    AAsset_close(asset);
    if (num != length) {
        LOGE("Couldn't read %s", path);
        delete[] buffer;
        return NULL;
    }
    buffer[length] = '\0';
    return buffer;
    return NULL;
}