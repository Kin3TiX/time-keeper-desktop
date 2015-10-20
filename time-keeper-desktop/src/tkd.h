#pragma once

#include "resource.h"
#include "tkd-notifier.h"

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#define APPMESSAGE WM_APP
#define APP_TRAYICON APPMESSAGE+200
#define MSG_SHOWCONFIG APPMESSAGE+300
#define MSG_QUIT APPMESSAGE+301
#define MSG_DEBUG APPMESSAGE+302

#define TRAYICON_ID 100

LRESULT CALLBACK mainWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int initMainWindow(HINSTANCE hInstance);
int initTrayIcon(HINSTANCE hInstance);
int displayContextMenu(HWND hWnd);