#include "tkd-pc.h"
#include "tkd-notifier.h"

NOTIFIER::NOTIFIER(HWND main) {

	appInstance = (HINSTANCE) (GetWindowLongPtr(main, GWLP_HINSTANCE));
	mainWindow = main;

}


NOTIFIER::~NOTIFIER() {

	DestroyWindow(notifierWindow);

}

int NOTIFIER::initialize() {

	WNDCLASS notifierWindowClass = { 0 };

	/* create pop under window class */
	LPSTR notifierWindowClassName = "time-keeper-notif";

	notifierWindowClass.cbClsExtra = 0;
	notifierWindowClass.cbWndExtra = 0;
	notifierWindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	notifierWindowClass.hIcon = LoadIcon(0, IDI_WINLOGO);
	notifierWindowClass.lpszMenuName = 0;
	notifierWindowClass.style = 0;
	notifierWindowClass.hbrBackground = 0;
	notifierWindowClass.lpfnWndProc = notifierWindowCallback;
	notifierWindowClass.hInstance = appInstance;
	notifierWindowClass.lpszClassName = notifierWindowClassName;

	/* register pop under window class */
	if( !RegisterClass(&notifierWindowClass) )
		return 1;

	/* set pop under window size and location */
	RECT screenSize;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &screenSize, 0);
	int windowHeight = screenSize.bottom / 10;
	int windowWidth = screenSize.right / 7;
	int windowY = screenSize.bottom - windowHeight - 5;
	int windowX = screenSize.right - windowWidth - 5;

	/* create main window */
	notifierWindow = CreateWindowEx(0,
									notifierWindowClassName,
									"Time Keeper Notification",
									WS_POPUPWINDOW,
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

	/* set window status flag */
	notifierLive = true;

	return 0;

}

int NOTIFIER::show() {

	AnimateWindow(notifierWindow, 100, AW_ACTIVATE | AW_SLIDE | AW_VER_NEGATIVE);

	return 0;

}

LRESULT CALLBACK notifierWindowCallback(HWND notifierWindow, UINT notifierMessage, WPARAM wParam, LPARAM lParam) {

	return DefWindowProc(notifierWindow, notifierMessage, wParam, lParam);

}
