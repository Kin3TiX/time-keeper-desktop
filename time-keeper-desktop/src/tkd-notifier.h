#pragma once

class NOTIFIER {

public:

	NOTIFIER();
	~NOTIFIER();

	int initialize(HINSTANCE, HWND, LPSTR);
	int show();

private:

	bool notifierLive;
	HWND notifierWindow;
	HINSTANCE appInstance;

};

LRESULT CALLBACK notifierWindowCallback(HWND, UINT, WPARAM, LPARAM);

