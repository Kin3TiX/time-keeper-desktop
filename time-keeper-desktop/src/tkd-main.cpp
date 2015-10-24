/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* standard includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-pc.h"
#include "tkd.h"

NOTIFYICONDATA trayIcon;
HWND mainWindow;
HICON trayIconImage;
NOTIFIER * popUnderWindow;
TIMEKEEPER * scheduler;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* application entry point ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	/* create main application window */
	if( initMainWindow(hInstance) )
		return 0;

	/* create tray icon */
	if( initTrayIcon(hInstance) ) {
		Shell_NotifyIcon(NIM_DELETE, &trayIcon);
		return 0;
	}

	popUnderWindow = new NOTIFIER(mainWindow);
	scheduler = new TIMEKEEPER(*popUnderWindow);

	/* create notifier window */
	if( popUnderWindow->initialize() ) {
		Shell_NotifyIcon(NIM_DELETE, &trayIcon);
		return 0;
	}

	/* load keyboard accelerator */
	HACCEL keyboardAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL));
	if( keyboardAccel == NULL ) {
		Shell_NotifyIcon(NIM_DELETE, &trayIcon);
		return 0;
	}
	
	/* start message loop */
	MSG windowMessage = { };
	while( GetMessage(&windowMessage, NULL, 0, 0) ) {

		/* check for keyboard events*/
		if( !TranslateAccelerator(mainWindow, keyboardAccel, &windowMessage) ) {

			/* no keyboard event, handle message */
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);

		}

	}

	delete(scheduler);
	delete(popUnderWindow);

	/* return OK;*/
	return 0;

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* main window callback ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
LRESULT CALLBACK mainWindowCallback(HWND mainWindow, UINT mainWindowMessage, WPARAM wParam, LPARAM lParam) {

	/* switch on dispatched message */
	switch( mainWindowMessage ) {

		case WM_DESTROY:

			/* add the icon */
			Shell_NotifyIcon(NIM_DELETE, &trayIcon);
			PostQuitMessage(0);
			break;

		/* system message received */
		case WM_SYSCOMMAND:

			/* system command */
			switch( wParam ) {

				/* minimize button hit */
				case SC_MINIMIZE:

					/* hide the window if minimized */
					ShowWindow(mainWindow, SW_HIDE);
					break;

				/* close button hit */
				case SC_CLOSE:
					
					/* hide the window if close button hit */
					ShowWindow(mainWindow, SW_HIDE);
					break;

					/* maximize button hit */
				case SC_MAXIMIZE:

					/* maximize the window */
					ShowWindow(mainWindow, SW_MAXIMIZE);
					break;

					/* restore button hit */
				case SC_RESTORE:

					/* restore the window */
					ShowWindow(mainWindow, SW_RESTORE);
					break;

				/* default handler */
				default:
					return DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);
					break;

			}

			break;

		/* tray icon message received */
		case APP_TRAYICON:

			/* switch on tray icon command*/
			switch(lParam) {

				/* tray icon double clicked */
				case WM_LBUTTONDBLCLK:

					/* show the configuration window*/
					ShowWindow(mainWindow, SW_SHOW);
					break;

				/* tray icon right clicked, show menu */
				case WM_RBUTTONDOWN:
				case WM_CONTEXTMENU:

					/* context menu routine */
					displayContextMenu(mainWindow);
					break;
				
				/* default handler */
				default:
					return DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);

			}

			break;

		/* paint the main window */
		case WM_PAINT:

			/* repaint the window area */
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(mainWindow, &ps);
				FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
				EndPaint(mainWindow, &ps);
			}
			break;

		/* receive commands */
		case WM_COMMAND:

			/* switch menu item */
			switch( LOWORD(wParam) ) {

				/* show the configuration (main) window */
				case MSG_SHOWCONFIG:
					ShowWindow(mainWindow, SW_SHOW);
					break;

				/* quit the application */
				case MSG_QUIT:
					DestroyWindow(mainWindow);
					break;

				/* debug item to allow the popUnder to be displayed */
				case MSG_DEBUG:
					popUnderWindow->show();
					break;

			}
			break;

		/* unknown message, dispatch default handler */
		default:

			return DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);
			break;

	}

	return DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);;

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* initialize main window ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int initMainWindow(HINSTANCE hInstance) {

	/* create main window class */
	WNDCLASS mainWindowClass = { 0 };
	LPSTR mainWindowClassName = "time-keeper-desktop";
	mainWindowClass.lpfnWndProc = mainWindowCallback;
	mainWindowClass.hInstance = hInstance;
	mainWindowClass.lpszClassName = mainWindowClassName;
	mainWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	mainWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	/* register main window class */
	RegisterClass(&mainWindowClass);

	/* set main window size and location */
	const HWND screen = GetDesktopWindow();
	RECT screenSize;
	GetWindowRect(screen, &screenSize);
	int windowHeight = screenSize.bottom / 2;
	int windowWidth = screenSize.right / 2;
	int windowY = windowHeight / 2;
	int windowX = windowWidth / 2;

	/* create main window */
	mainWindow = CreateWindowEx(0,
								mainWindowClassName,
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
	if( mainWindow == NULL ) {
		return 1;
	}

	/* show window initially hidden */
	ShowWindow(mainWindow, SW_HIDE);
	UpdateWindow(mainWindow);

	/* return OK */
	return 0;

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* initialize tray icon ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int initTrayIcon(HINSTANCE hInstance) {

	/* create tray icon image from resource file */
	trayIconImage = (HICON) LoadImage(hInstance,
									  MAKEINTRESOURCE(IDI_TRAYICON),
									  IMAGE_ICON,
									  GetSystemMetrics(SM_CXSMICON),
									  GetSystemMetrics(SM_CYSMICON),
									  LR_DEFAULTCOLOR);

	/* configure tray icon */
	trayIcon.uID = TRAYICON_ID;
	trayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	trayIcon.hWnd = mainWindow;
	trayIcon.hIcon = trayIconImage;
	trayIcon.uCallbackMessage = APP_TRAYICON;

	/* add the icon */
	Shell_NotifyIcon(NIM_DELETE, &trayIcon);
	Shell_NotifyIcon(NIM_ADD, &trayIcon);

	/* animate the context menu */
	bool menuAnimation = true;
	bool menuFade = false;
	SystemParametersInfo(SPI_SETMENUANIMATION, 0, &menuAnimation, 0);
	SystemParametersInfo(SPI_SETMENUFADE, 0, &menuFade, 0);
	
	/* clear strange tray error */
	if( GetLastError() == 1008 )
		SetLastError(NO_ERROR);

	/* return OK */
	return 0;

}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* display right click context menu ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int displayContextMenu(HWND hWnd) {

	/* create the context menu */
	HMENU contextMenu = CreatePopupMenu();
	AppendMenu(contextMenu, MF_STRING, MSG_SHOWCONFIG, "Configure");
	AppendMenu(contextMenu, MF_STRING, MSG_DEBUG, "DEBUG");
	AppendMenu(contextMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(contextMenu, MF_STRING, MSG_QUIT, "Exit");

	/* set the application menu on top */
	SetForegroundWindow(mainWindow);

	/* get cursor position for displaying the menu */
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	/* track user selection */
	TrackPopupMenuEx(contextMenu, 
				   TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERNEGANIMATION,
				   cursorPos.x,
				   cursorPos.y,
				   mainWindow,
				   NULL);

	/* destroy the menu */
	DestroyMenu(contextMenu);

	return 0;

}