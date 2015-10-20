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

#define TRAYICON_ID 100

LRESULT CALLBACK mainWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int initMainWindow(HINSTANCE hInstance);
int initTrayIcon(HINSTANCE hInstance);