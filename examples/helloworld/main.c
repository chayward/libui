// 2020 09 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../ui.h"

uiWindow *mainwin;

static int onClosing(/*@unused@*/ uiWindow *w, /*@unused@*/ void *data)
{
	uiControlDestroy(uiControl(mainwin));
	uiQuit();
	return 0;
}

static int shouldQuit(/*@unused@*/ void *data)
{
	uiControlDestroy(uiControl(mainwin));
	return 1;
}

int main(/*@unused@*/ int argc, /*@unused@*/ char **argv)
{
	uiBox *vbox;
	uiLabel *label;

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

	mainwin = uiNewWindow("libui HelloWorld Example", 320, 240, 1);
	uiWindowSetMargined(mainwin, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);
	uiWindowSetChild(mainwin, (uiControl *) vbox);

	label = uiNewLabel( "Hello, World!" ); 
    	uiBoxAppend(vbox, (uiControl *) label, 0 ); 
    	uiBoxAppend(vbox, (uiControl *) uiNewLabel("Below the World."), 0); 

	uiControlShow(uiControl(mainwin));
	uiMain();
	uiUninit();
	return 0;
}
