/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* notifier interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once
#include "resource.h"

/* notifier class definition */
class NOTIFIER {

	/* public members */
public:

	/* constructor, destructor */
	NOTIFIER(HWND);
	~NOTIFIER();

	/* notifier public interface */
	int initialize();
	int show();
	int hide();

	/* notifier visible flag */
	bool visible;

	/* notifier window activity flag */
	bool active;

	/* private members */
private:

	/* notifier private data */
	bool notifierLive = false;
	HWND notifierWindow;
	HINSTANCE appInstance;
	HWND mainWindow;

};

