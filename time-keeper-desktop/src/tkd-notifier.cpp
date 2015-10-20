#include "tkd-pc.h"
#include "tkd-notifier.h"

NOTIFIER::NOTIFIER(HINSTANCE caller, HWND main) {

	appInstance = caller;
	mainWindow = main;

}


NOTIFIER::~NOTIFIER() {


}

int NOTIFIER::initialize() {

	WNDCLASS notifierWindowClass = { };

	/* create pop under window class */
	LPSTR notifierWindowClassName = "time-keeper-notif";

	notifierWindowClass.lpfnWndProc = notifierWindowCallback;
	notifierWindowClass.hInstance = appInstance;
	notifierWindowClass.lpszClassName = notifierWindowClassName;
	notifierWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	notifierWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	/* register pop under window class */
	RegisterClass(&notifierWindowClass);

	/* set pop under window size and location */
	const HWND screen = GetDesktopWindow();
	RECT screenSize;
	GetWindowRect(screen, &screenSize);
	int windowHeight = screenSize.bottom / 10;
	int windowWidth = screenSize.right / 10;
	int windowY = screenSize.bottom - windowHeight - 5;
	int windowX = screenSize.right - windowWidth - 5;

	/* create main window */
	notifierWindow = CreateWindowEx(0,
									notifierWindowClassName,
									"Time Keeper Notification",
									WS_OVERLAPPEDWINDOW,
									windowX,
									windowY,
									windowWidth,
									windowHeight,
									NULL,
									NULL,
									appInstance,
									NULL);

	/* check everything is OK */
	if( notifierWindow == NULL ) {
		notifierLive = false;
		return 1;
	}

	/* show window initially hidden */
	ShowWindow(notifierWindow, SW_HIDE);
	UpdateWindow(notifierWindow);

	/* set window status flag */
	notifierLive = true;

	return 0;

}

int NOTIFIER::show() {

	AnimateWindow(notifierWindow, 200, AW_ACTIVATE | AW_SLIDE | AW_VER_NEGATIVE);

	return 0;

}

LRESULT CALLBACK notifierWindowCallback(HWND notifierWindow, UINT notifierMessage, WPARAM wParam, LPARAM lParam) {

	DefWindowProc(notifierWindow, notifierMessage, wParam, lParam);
	
	return 0;

}
