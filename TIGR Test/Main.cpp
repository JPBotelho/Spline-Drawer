#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif

#include "ControlPoint.h"
#include <stdio.h>
#include "wtypes.h"
#include <iostream>
#include "Main.h"

int screenResHoriz = 0;
int screenResVert = 0;

Tigr *screen;
int mouseMask = 0;

bool mouseDownPrevFrame = 0;
bool mouseDownCurrFrame = 0;


bool dragging;
int cursorX, cursorY;

ControlPoint* controlPoints[3];
//Index of the controlPoint that's currently being dragged
int activeDrag;
int startx, starty;

int main(int argc, char *argv[])
{
	GetScreenRes();
	screen = tigrWindow(320*3, 240*3, "Hello", 0);
	ControlPoint* point = new ControlPoint(0.1f, .1f, .15f, screen);
	ControlPoint* point1 = new ControlPoint(.1f, .5f, .15f, screen);
	ControlPoint* point2 = new ControlPoint(.5f, .1f, .15f, screen);

	controlPoints[0] = point;
	controlPoints[1] = point1;
	controlPoints[2] = point2;

	UpdateMouse();
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
	{
		UpdateMouse();

		if (OnMouseDown() && !dragging)
		{
			GetPointAtCursor();
		}
		if (OnMouseExit() && dragging)
		{
			dragging = false;
		}

		if (dragging)
		{
			controlPoints[activeDrag]->x = cursorX;
			controlPoints[activeDrag]->y = cursorY;
		}
		tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
		for (int i = 0; i < sizeof(controlPoints) / sizeof(controlPoints[0]); i++)
		{
			controlPoints[i]->Draw();
		}
		DrawLines();
		tigrUpdate(screen);
	}
	tigrFree(screen);
	return 0;
}

bool OnMouseDown() { return !mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseStay() { return mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseExit() { return mouseDownPrevFrame && !mouseDownCurrFrame; }

bool LMBdown(int bitmask) { return bitmask & (1 << 0); }
bool MMBdown(int bitmask) { return bitmask & (1 << 1); }
bool RMBdown(int bitmask) { return bitmask & (1 << 2); }


void GetScreenRes()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	screenResHoriz = desktop.right;
	screenResVert = desktop.bottom;

	//printf("%d\n", horizontal);
	//printf("%d", vertical);
}

void GetPointAtCursor()
{
	for (int i = 0; i < sizeof(controlPoints) / sizeof(controlPoints[0]); i++)
	{
		float scaledCursorX = (float)cursorX / screen->w;
		float scaledCursorY = (float)cursorY / screen->h;
		if (controlPoints[i]->Intersects(scaledCursorX, scaledCursorY))
		{
			activeDrag = i;
			dragging = true;
			break;
		}
	}
}

void UpdateMouse()
{
	int garbage;
	tigrMouse(screen, &cursorX, &cursorY, &mouseMask);
	mouseDownPrevFrame = mouseDownCurrFrame;
	mouseDownCurrFrame = LMBdown(mouseMask);
}

void DrawLines()
{
	int pointcount = sizeof(controlPoints) / sizeof(controlPoints[0]);
	for (int i = 0; i < pointcount; i++)
	{
		int nextPoint = i != pointcount - 1 ? i + 1 : 0;
		int x0 = controlPoints[i]->x;
		int y0 = controlPoints[i]->y;
		int x1 = controlPoints[nextPoint]->x;
		int y1 = controlPoints[nextPoint]->y;

		tigrLine(screen, x0, y0, x1, y1, tigrRGB(0, 255, 0));
	}
}