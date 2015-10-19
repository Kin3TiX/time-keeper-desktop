#pragma once

class notifier {

public:

	notifier();
	~notifier();

	int showWindow();

private:

	HWND notifierWindow;
	WNDCLASS notifierWindowClass;

	LRESULT CALLBACK notifierWindowCallback(HWND, UINT, WPARAM, LPARAM);

};

