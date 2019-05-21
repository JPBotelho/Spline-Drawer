#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif

#include "ControlPoint.h"
#include <stdio.h>
//so if (buttons & (1 << 0)) for left, (1 << 1) for middle and (1 << 2) for right
bool LMBdown(int bitmask) { return bitmask & (1 << 0); }
bool MMBdown(int bitmask) { return bitmask & (1 << 1); }
bool RMBdown(int bitmask) { return bitmask & (1 << 2); }


bool mouseDownPrevFrame = 0;
bool mouseDownCurrFrame = 0;

bool OnMouseDown() { return !mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseStay() { return mouseDownPrevFrame && mouseDownCurrFrame; }
bool OnMouseExit() { return mouseDownPrevFrame && !mouseDownCurrFrame; }

int mouseMask = 0;

int cursorX, cursorY;

void UpdateMouse(Tigr* screen)
{
	int garbage;
	tigrMouse(screen, &cursorX, &cursorY, &mouseMask);
	mouseDownPrevFrame = mouseDownCurrFrame;
	mouseDownCurrFrame = LMBdown(mouseMask);
}

bool dragging;
int startx, starty;
void StartDrag()
{
	/*
	if(intersection with point)
		draggingPoint=
	*/
	dragging = true;
}

void StopDragging()
{
	dragging = false;
}

int main(int argc, char *argv[])
{
	Tigr *screen = tigrWindow(320, 240, "Hello", 0);
	ControlPoint point = ControlPoint(320 / 2, 240 / 2, 25, screen);

	UpdateMouse(screen);
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
	{
		UpdateMouse(screen);

		if (OnMouseDown() && !dragging)
		{
			StartDrag();
			printf("MouseDown");
		}
		if (OnMouseExit() && dragging)
		{
			StopDragging();
			printf("MouseUp");
		}

		if (dragging)
		{
			point.x = cursorX;
			point.y = cursorY;
		}
		tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
		point.Draw();

		tigrUpdate(screen);
	}
	tigrFree(screen);
	return 0;
}

