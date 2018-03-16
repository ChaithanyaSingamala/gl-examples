#include <iostream>
#include "application.h"
#include "helper.h"

int main(int argc, char **argv)
{
	Interface *appInterface = new Interface();
	PrintOGLESInfo();

	Application *application = createApplication();
	application->SetInterface(appInterface);
	application->Init();


	while (!appInterface->IsExit()) {
		application->Update();
		application->Render();
		appInterface->Update();
	}

	delete application;

	return 0;
}
