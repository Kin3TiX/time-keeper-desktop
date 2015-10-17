#pragma once

#include "resource.h"

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#define APPMESSAGE WM_APP
#define APP_TRAYICON APPMESSAGE+200

#define TRAYICON_ID 100

WNDCLASS mainWindowClass = { };
NOTIFYICONDATA trayIcon;
HWND mainWindow;
HICON trayIconImage;

LRESULT CALLBACK mainWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int initMainWindow(HINSTANCE hInstance);
int initTrayIcon(HINSTANCE hInstance);