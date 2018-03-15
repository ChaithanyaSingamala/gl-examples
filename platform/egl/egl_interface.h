#pragma once
#include <string>
#include "EGL\egl.h"
#include "log.h"

class EGLInterface
{
	bool exit = false;
	int width = 800;
	int height = 600;

	EGLNativeDisplayType display = nullptr;
	EGLNativeWindowType window = nullptr;
	EGLDisplay eglDisplay = nullptr;
	EGLSurface eglWindowSurface = nullptr;
	EGLContext eglContext = nullptr;

	void WinLoop() 
	{
		MSG msg = { 0 };
		int done = 0;
		DWORD lastTime = GetTickCount();

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			//break;
		}

	}
#ifdef _WIN32
	static LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT  lRet = 1;

		switch (uMsg)
		{
		case WM_CREATE:
			break;

		case WM_SIZE:
		{
			EGLInterface* i = (EGLInterface*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (i) InvalidateRect(i->Window(), NULL, FALSE);

		}

		case WM_PAINT:
		{
			EGLInterface* i = (EGLInterface*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			//if (esContext && esContext->drawFunc)
			//	esContext->drawFunc(esContext);

			if (i)
				ValidateRect(i->Window(), NULL);
		}
		break;

		case WM_CLOSE:
			PostQuitMessage(0);
			{
				EGLInterface* i = (EGLInterface*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
				DestroyWindow(hWnd);
				if (i)
					i->SetExit();
			}

			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}

		return lRet;
	}
	EGLBoolean WinCreate(std::string title, int w, int h) 
	{
		WNDCLASS wndclass = { 0 };
		DWORD    wStyle = 0;
		RECT     windowRect;
		HINSTANCE hInstance = GetModuleHandle(NULL);

		wndclass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = (WNDPROC)WindowProc;
		wndclass.hInstance = hInstance;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszClassName = TEXT("opengles2.0");

		if (!RegisterClass(&wndclass))
			return FALSE;

		wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_SIZEBOX;

		// Adjust the window rectangle so that the client area has
		// the correct number of pixels
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = w;
		windowRect.bottom = h;

		AdjustWindowRect(&windowRect, wStyle, FALSE);

		window = CreateWindow(
			TEXT("opengles2.0"),
			title.c_str(),
			wStyle,
			0,
			0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL);

		SetWindowLongPtr(window, GWLP_USERDATA, (LONG)(LONG_PTR)this);

		display = GetDC(window);

		if (window == NULL)
			return EGL_FALSE;

		ShowWindow(window, TRUE);

		return EGL_TRUE;
	}
#endif
	void Setup()
	{
#ifdef _WIN32
		WinCreate("OpenGL window", 800, 600);
#endif

		EGLint ogl_attribList[] =
		{
			EGL_BUFFER_SIZE,	0,
			EGL_DEPTH_SIZE,     16,
			EGL_STENCIL_SIZE,   EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, 1,
			EGL_SAMPLES,        2,
			EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
#if EGL_OPENGL_ES3_BIT
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
#elif EGL_OPENGL_ES3_BIT_KHR
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
#else
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
#endif
			EGL_NONE
		};

		int ret = 0;

		EGLint majorVersion;
		EGLint minorVersion;
		EGLint numConfigs, numConfigs0;

		EGLint gl_context_attribs[] = {
#if EGL_OPENGL_ES3_BIT
			EGL_CONTEXT_MAJOR_VERSION, 3,
			EGL_CONTEXT_MINOR_VERSION, 2,
#elif EGL_OPENGL_ES3_BIT_KHR
			EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
			EGL_CONTEXT_MINOR_VERSION_KHR, 1,
#else
			EGL_CONTEXT_CLIENT_VERSION, 2,
#endif
			EGL_NONE
		};

#ifdef EGL_API_FB
		EGLNativeDisplayType  eglNativeDisplay;
		eglNativeDisplay = fbGetDisplayByIndex(0);

		// Associate the display with EGL.
		eglDisplay = eglGetDisplay(eglNativeDisplay);
		window = fbCreateWindow(eglNativeDisplay, 0, 0, 0, 0);
#else
		eglDisplay = eglGetDisplay(display);
#endif



		eglInitialize(eglDisplay, &majorVersion, &minorVersion);

		eglBindAPI(EGL_OPENGL_ES_API);

		eglGetConfigs(eglDisplay, NULL, 0, &numConfigs);

		EGLConfig eglConfig;

		// worst case, just let's select the first one  
		eglChooseConfig(eglDisplay, ogl_attribList, &eglConfig, 1, &numConfigs0);

		eglWindowSurface = eglCreateWindowSurface(eglDisplay, eglConfig, window, (EGLint*)NULL);

		if (eglWindowSurface == EGL_NO_SURFACE)
		{
			Log("ERROR: %s: eglCreateWindowSurface: %x", __func__, eglGetError());
		}
		else
		{
			Log("%s: eglCreateWindowSurface ok", __func__);
		}

		eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, gl_context_attribs);

		if (eglContext == EGL_NO_CONTEXT)
		{
			Log("ERROR: %s: eglCreateContext: %d", __func__, eglGetError());
		}
		else
		{
			Log("%s:eglCreateContext ok", __func__);
		}

		ret = eglMakeCurrent(eglDisplay, eglWindowSurface, eglWindowSurface, eglContext);
		if (ret == EGL_FALSE)
		{
			Log("ERROR: %s: eglMakeCurrent: %d", __func__, eglGetError());
		}
		else
		{
			Log("%s:eglMakeCurrent ok", __func__);
		}

		ret = eglSwapInterval(eglDisplay, 0);
		if (ret != EGL_TRUE)
		{
			Log("ERROR: %s: eglSwapInterval: %d", __func__, eglGetError());
		}
		else
		{
			Log("%s:eglSwapInterval set to 0 ok", __func__);
		}

		Log("EGL  initialization was succesful!");

		// Get screen width and height
		eglQuerySurface(eglDisplay, eglWindowSurface, EGL_WIDTH, &width);
		eglQuerySurface(eglDisplay, eglWindowSurface, EGL_HEIGHT, &height);

		Log("width height %d %d ", width, height);


	}
public:
	EGLInterface() {
		Log("Starting EGLInterface...");
		Setup();
	}
	virtual ~EGLInterface() {
		Log("Exiting EGLInterface...");
	}

	virtual void Update() {
#ifdef _WIN32
		WinLoop();
#endif

		eglSwapBuffers(eglDisplay, eglWindowSurface);
	}
	virtual bool IsExit() {
		return exit;
	}
	virtual void SetExit() {
		exit = true;
	}

	virtual EGLNativeWindowType Window() { return window; }


	virtual unsigned short Width(unsigned short _width = 0) { return width = (_width == 0) ? width : _width; }
	virtual unsigned short Height(unsigned short _height = 0) { return height = (_height == 0) ? height : _height; }
};


