#include <jni.h>
#include <string>
#include <application.h>
#include <helper.h>

#include "platform.h"
#include "AndroidHelper.h"
#include "android_interface.h"


extern "C"
JNIEXPORT jstring

JNICALL
Java_gles_opengl_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static Application *application;
static AndroidInterface *appInterface;

extern "C"
JNIEXPORT void JNICALL
Java_gles_opengl_MyRenderer_nativeSurfaceCreate(
        JNIEnv *env,
        jclass type,
        jobject assetManager) {

    AndroidHelper::setEnvAndAssetManager(env, assetManager);

    appInterface = new AndroidInterface();
	PrintOGLESInfo();
	application = createApplication();
	application->SetInterface(appInterface);
	application->Init();


}

extern "C"
JNIEXPORT void JNICALL
Java_gles_opengl_MyRenderer_nativeSurfaceChange(
        JNIEnv *env,
        jclass type,
        jint width,
        jint height) {

    appInterface->Height(height);
    appInterface->Width(width);
    application->ViewportChanged(width,height);
}

extern "C"
JNIEXPORT void JNICALL
Java_gles_opengl_MyRenderer_nativeDrawFrame(
        JNIEnv *env,
        jclass type) {

    application->Update();
    application->Render();
    appInterface->Update();


}
