#pragma once

class NOTIFIER {

public:

	NOTIFIER();
	~NOTIFIER();

	int initialize(HINSTANCE, HWND);
	int show();

private:

	bool notifierLive = false;

	HWND notifierWindow;
	WNDCLASS notifierWindowClass;
	HINSTANCE appInstance;

};

