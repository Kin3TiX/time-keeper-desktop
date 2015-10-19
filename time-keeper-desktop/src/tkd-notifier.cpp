#include "tkd-pc.h"
#include "tkd-notifier.h"

notifier::notifier() {

	/* create main window class */
	LPSTR notifierWindowClassName = "time-keeper-desktop";

	notifierWindowClass.lpfnWndProc = notifierWindowCallback;
	notifierWindowClass.hInstance = hInstance;
	notifierWindowClass.lpszClassName = notifierWindowClassName;
	notifierWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	notifierWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	/* register main window class */
	RegisterClass(&notifierWindowClass);

	/* set main window size and location */
	const HWND screen = GetDesktopWindow();
	RECT screenSize;
	GetWindowRect(screen, &screenSize);
	int windowHeight = screenSize.bottom / 2;
	int windowWidth = screenSize.right / 2;
	int windowY = windowHeight / 2;
	int windowX = windowWidth / 2;

	/* create main window */
	notifierWindow = CreateWindowEx(0,
								notifierWindowClassName,
								"Time Keeper Desktop",
								WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW,
								windowX,
								windowY,
								windowWidth,
								windowHeight,
								NULL,
								NULL,
								hInstance,
								NULL);

	/* check everything is OK */
	if( notifierWindow == NULL ) {
		return 1;
	}

	/* show window initially hidden */
	ShowWindow(notifierWindow, SW_HIDE);
	UpdateWindow(notifierWindow);

}


notifier::~notifier() { 


}

int notifier::showWindow() {

	return 0;

}

LRESULT notifier::notifierWindowCallback(HWND, UINT, WPARAM, LPARAM) {
	
	return 0;

}
