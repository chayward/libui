// 2020 09 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../ui.h"

static uiWindow *mainwin;

static int onClosing(/*@unused@*/ uiWindow *w, /*@unused@*/ void *data)
{
	uiControlDestroy(uiControl(mainwin));
	uiQuit();
	return 0;
}

static int shouldQuit(/*@unused@*/ /*@null@*/ void *data)
{
	uiControlDestroy(uiControl(mainwin));
	return 1;
}

// Callback executed when button pressed.
static void onClicked(/*@unused@*/ uiButton *b, /*@unused@*/ /*@null@*/ void *data)
{
	fprintf(stdout, "Button Pressed.\n");
	(void) fflush(stdout);
}



int main(/*@unused@*/ int argc, /*@unused@*/ char **argv)
{
	uiBox *vbox;
	uiButton *button;

	uiInitOptions o;
	const char *err;

	memset(&o, 0, sizeof (uiInitOptions));
	err = uiInit(&o);
	if (err != NULL) {
		fprintf(stderr, "Error initializing ui: %s\n", err);
		uiFreeInitError(err);
		return -1;
	}

	uiOnShouldQuit(shouldQuit, NULL);

	mainwin = uiNewWindow("libui Dialog Example", 320, 240, 1);
	uiWindowSetMargined(mainwin, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);
	uiWindowSetChild(mainwin, (uiControl *) vbox);

	button = uiNewButton( "Press Me" ); 
	uiButtonOnClicked(button, onClicked, NULL);
    	uiBoxAppend(vbox, (uiControl *) button, 0 ); 

	uiControlShow(uiControl(mainwin));
	uiMain();
	uiUninit();
	return 0;
}
