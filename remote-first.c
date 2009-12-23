#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/keysym.h>

int main(void)
{
	Display *display = XOpenDisplay("10.55.55.44:0");
	if(!display)
	{
		printf("Open display 10.55.55.44:0 failed\n");
		return 0;
	}
	//Display *display = XOpenDisplay(NULL);
	int screen = DefaultScreen(display);

	int width = DisplayWidth(display, screen)/2;
	int height = DisplayHeight(display, screen)/2;

	int black_pixel = BlackPixel(display, screen);
	int white_pixel = WhitePixel(display, screen);

	Window win = XCreateSimpleWindow(display, RootWindow(display, screen), 0,0, width, height, 3, black_pixel, white_pixel);
	
	XSelectInput(display, win, ExposureMask|KeyPressMask|StructureNotifyMask);

	XMapWindow(display, win);

	GC gc = XCreateGC(display, win, 0, NULL);

	while(1)
	{
		XEvent event = {0};
		XNextEvent(display, &event);
		//if(event.type == MapNotify)
		//	break;
		switch(event.type)
		{
			case ConfigureNotify:
				{
					width = event.xconfigure.width;
					height = event.xconfigure.height;
					break;
				}
			case Expose:
				{
					XSetForeground(display, gc, WhitePixel(display, screen));
					XFillRectangle(display, win, gc, 0, 0, width, height);
					XSetForeground(display, gc, BlackPixel(display, screen));
					XDrawString(display, win, gc, width/2, height/2, "XWindow", 7);
					break;
				}
			case KeyPress:
				{
					if(event.xkey.keycode == XKeysymToKeycode(display, XK_Escape))
					{
						XFreeGC(display, gc);
						XCloseDisplay(display);
						return 0;
					}
				}
			default:
				break;
		}
	}
	//XDrawLine(display, win, gc, 10, 160, 180, 20);
	//XFlush(display);
	//sleep(3);
	return 0;
}
