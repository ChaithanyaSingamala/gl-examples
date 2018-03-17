#pragma once
#include <iostream>
#include <assert.h>

#define ENABLE_LOG 1

#ifdef ENABLE_LOG
#if ANDROID_BUILD
#include <android/log.h>
	#define  LOG_TAG    "OpenGLES-android"
	#define  Log(...)   __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
	#define  LogI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
	#define  LogD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
	#define  LogE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define	 Log(...)	{printf(__VA_ARGS__); printf("\n");}
#define  LogI(...)	{printf("Info:");  printf(__VA_ARGS__); printf("\n");}
#define  LogD(...)  {printf("Debug:"); printf(__VA_ARGS__); printf("\n");}
#define  LogE(...)  {printf("Error:"); printf(__VA_ARGS__); printf("\n"); assert(0);}
#endif
#else
#define	 Log(...)	
#define  LogI(...)	
#define  LogD(...)  
#define  LogE(...)  
#endif

std::string ReadFromFile(std::string _filename);

void PrintOGLESInfo(bool printExtensions=false);

void PrintEGLInfo(bool printExtensions = false);

long currentTimeInMS();
