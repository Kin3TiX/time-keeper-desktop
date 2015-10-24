#pragma once

#include "resource.h"

class NOTIFIER {

public:

	NOTIFIER(HWND);
	~NOTIFIER();

	int initialize();
	int show();
	int hide();

	bool visible;

private:

	bool notifierLive = false;
	HWND notifierWindow;
	HINSTANCE appInstance;
	HWND mainWindow;

};

LRESULT CALLBACK notifierWindowCallback(HWND, UINT, WPARAM, LPARAM);

