#pragma once
#include "platform.h"

#include <vector>
class Application
{
protected:
	Interface *appInterface;
public:
	Application(Interface *_appInterface);
	virtual ~Application();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void ViewportChanged(int _width, int _height);

	static void CreateRunApplication() {
		Interface *appInterface = new Interface();

		Application *application = new Application(appInterface);
		application->Init();

		while (!appInterface->IsExit()) {
			application->Update();
			application->Render();
			appInterface->Update();
		}

		delete application;
	}

};

