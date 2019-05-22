#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif

#include "ControlPoint.h"
#include <stdio.h>

Tigr *screen;
int mouseMask = 0;

bool LMBdown(int bitmask) { return bitmask & (1 << 0); }
bool MMBdown(int bitmask) { return bitmask & (1 << 1); }
bool RMBdown(int bitmask) { return bitmask & (1 << 2); }

bool mouseDownPrevFrame = 0;
bool mouseDownCurrFrame = 0;

bool OnMouseDown() { return !mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseStay() { return mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseExit() { return mouseDownPrevFrame && !mouseDownCurrFrame; }

bool dragging;
int cursorX, cursorY;

ControlPoint* controlPoints[3];
//Index of the controlPoint that's currently being dragged
int activeDrag;

void GetPointAtCursor()
{
	for (int i = 0; i < sizeof(controlPoints) / sizeof(controlPoints[0]); i++)
	{
		if (controlPoints[i]->Intersects(cursorX, cursorY))
		{
			activeDrag = i;
			dragging = true;
			break;
		}
	}
}

void UpdateMouse(Tigr* screen)
{
	int garbage;
	tigrMouse(screen, &cursorX, &cursorY, &mouseMask);
	mouseDownPrevFrame = mouseDownCurrFrame;
	mouseDownCurrFrame = LMBdown(mouseMask);
}

int startx, starty;
void StartDrag()
{
	GetPointAtCursor();
}

void DrawLines()
{
	int pointcount = sizeof(controlPoints) / sizeof(controlPoints[0]);
	for (int i = 0; i < pointcount; i++)
	{
		int nextPoint = i != pointcount -1 ? i + 1 : 0;
		int x0 = controlPoints[i]->x;
		int y0 = controlPoints[i]->y;
		int x1 = controlPoints[nextPoint]->x;
		int y1 = controlPoints[nextPoint]->y;

		tigrLine(screen, x0, y0, x1, y1, tigrRGB(0, 255, 0));
	}
}

int main(int argc, char *argv[])
{
	screen = tigrWindow(320*3, 240*3, "Hello", 0);
	ControlPoint* point = new ControlPoint(320 / 2, 240 / 2, 25, screen);
	ControlPoint* point1 = new ControlPoint(320 / 3, 240 / 2, 25, screen);
	ControlPoint* point2 = new ControlPoint(320 / 3*2, 240 / 2, 25, screen);

	controlPoints[0] = point;
	controlPoints[1] = point1;
	controlPoints[2] = point2;

	UpdateMouse(screen);
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
	{
		UpdateMouse(screen);

		if (OnMouseDown() && !dragging)
		{
			StartDrag();
			//printf("MouseDown");
		}
		if (OnMouseExit() && dragging)
		{
			dragging = false;
			//printf("MouseUp");
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

