#pragma once

class NOTIFIER {

public:

	NOTIFIER(HINSTANCE, HWND);
	~NOTIFIER();

	int initialize();
	int show();

private:

	bool notifierLive;
	HWND notifierWindow;
	HINSTANCE appInstance;
	HWND mainWindow;

};

LRESULT CALLBACK notifierWindowCallback(HWND, UINT, WPARAM, LPARAM);

