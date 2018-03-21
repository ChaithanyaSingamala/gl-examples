#include <iostream>
#include "application.hpp"
#include "helper.h"

int main(int argc, char **argv)
{
	Interface *appInterface = new Interface();
	PrintOGLESInfo();

	Application *application = createApplication();
	application->SetInterface(appInterface);
	application->Init();
	application->ViewportChanged(appInterface->Width(), appInterface->Height());


	while (!appInterface->IsExit()) {
		application->Update();
		application->Render();
		appInterface->Update();
	}

	delete application;

	return 0;
}
