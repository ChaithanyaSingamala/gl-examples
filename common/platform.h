#pragma once

#ifdef ENABLE_EGL
#include "egl_interface.h"
typedef  EGLInterface Interface;
#endif

#ifdef ANDROID_BUILD
#include "android_interface.h"
typedef  AndroidInterface Interface;
#endif
