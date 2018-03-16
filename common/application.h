#pragma once
#include "platform.h"

#include <vector>
class Application
{
public:
	Application() {}
	virtual ~Application() {}
	Interface *appInterface;
	virtual void SetInterface(Interface *_appInterface) { appInterface = _appInterface; }
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ViewportChanged(int _width, int _height) = 0;

};

//need to create by example application
extern Application *createApplication();

