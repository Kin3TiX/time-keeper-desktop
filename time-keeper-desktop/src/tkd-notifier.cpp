/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* notifier implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-pc.h"
#include "tkd-notifier.h"

/* notifier window procedure callback */
/* can this be a static member function instead?? */
LRESULT CALLBACK notifierWindowCallback(HWND, UINT, WPARAM, LPARAM);

/* constructor */
NOTIFIER::NOTIFIER(HWND main) {

	/* set application instance, store parent window and visible flag false */
	appInstance = (HINSTANCE) (GetWindowLongPtr(main, GWLP_HINSTANCE));
	mainWindow = main;
	visible = false;

}

/* destructor */
NOTIFIER::~NOTIFIER() {

	/* destroy the notifier window itself */
	DestroyWindow(notifierWindow);

}

/* initialize the notifier */
int NOTIFIER::initialize() {

	/* create pop under window class */
	WNDCLASS notifierWindowClass = { 0 };
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
									(WS_POPUPWINDOW | WS_EX_TOOLWINDOW),
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

	/* make the popup topmost */
	SetWindowPos(notifierWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	/* remove the taskbar icon */
	long style = GetWindowLong(notifierWindow, GWL_STYLE);
	style &= ~(WS_VISIBLE);
	style |= WS_EX_TOOLWINDOW;
	style &= ~(WS_EX_APPWINDOW);
	ShowWindow(notifierWindow, SW_HIDE);
	SetWindowLong(notifierWindow, GWL_STYLE, style); // set the style
	ShowWindow(notifierWindow, SW_SHOW);
	ShowWindow(notifierWindow, SW_HIDE);

	/* set window status flag */
	notifierLive = true;

	return 0;

}

/* show the notifier window */
int NOTIFIER::show() {

	/* slide the window in from the bottom */
	AnimateWindow(notifierWindow, 100, AW_ACTIVATE | AW_SLIDE | AW_VER_NEGATIVE);
	visible = true;

	return 0;

}

/* hide the notifier window */
int NOTIFIER::hide() {

	/* hide the window */
	ShowWindow(notifierWindow, SW_HIDE);
	visible = false;

	return 0;

}

/* notifier popup window procedure callback */
LRESULT CALLBACK notifierWindowCallback(HWND notifierWindow, UINT notifierMessage, WPARAM wParam, LPARAM lParam) {

	/* return default functionality (NEEDS IMPLEMENTATION) */
	return DefWindowProc(notifierWindow, notifierMessage, wParam, lParam);

}
