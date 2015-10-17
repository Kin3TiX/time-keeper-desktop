/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* standard includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-pc.h"
#include "tkd.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* application entry point ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	/* create main application window */
	if( initMainWindow(hInstance) )
		return 0;

	/* create tray icon */
	if( initTrayIcon(hInstance) )
		return 0;

	/* load keyboard accelerator */
	HACCEL keyboardAccel = LoadAccelerators(hInstance, "");
	if( keyboardAccel == NULL )
		return 0;
	
	/* start message loop */
	MSG mainWindowMessage = { };
	while( GetMessage(&mainWindowMessage, NULL, 0, 0) ) {

		/* check for keyboard events*/
		if( !TranslateAccelerator(mainWindow, keyboardAccel, &mainWindowMessage) ) {

			/* no keyboard event, handle message */
			TranslateMessage(&mainWindowMessage);
			DispatchMessage(&mainWindowMessage);

		}

	}

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

				/* window moved */
				case SC_MOVE:

					/* provide default move functionality*/
					DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);
					break;

				/* minimize button hit */
				case SC_MINIMIZE:

					/* hide the window if minimized */
					ShowWindow(mainWindow, SW_HIDE);
					break;

				/* close button hit */
				case SC_CLOSE:
					
					/* destroy window */
					DestroyWindow(mainWindow);
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

			}

			break;

		case WM_PAINT:

			/* repaint the window area */
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(mainWindow, &ps);
				FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
				EndPaint(mainWindow, &ps);
			}
			break;

		/* unknown message, dispatch default handler */
		default:

			return DefWindowProc(mainWindow, mainWindowMessage, wParam, lParam);
			break;

	}

	/* return OK */
	return 0;

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* initialize main window ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int initMainWindow(HINSTANCE hInstance) {

	/* create main window class */
	LPSTR mainWindowClassName = "time-keeper-desktop";

	mainWindowClass.lpfnWndProc = mainWindowCallback;
	mainWindowClass.hInstance = hInstance;
	mainWindowClass.lpszClassName = mainWindowClassName;

	/* register main window class */
	RegisterClass(&mainWindowClass);

	/* create main window */
	mainWindow = CreateWindowEx(0,
								mainWindowClassName,
								"Time Keeper Desktop",
								WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
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
	Shell_NotifyIcon(NIM_ADD, &trayIcon);

	/* return OK */
	return 0;

}