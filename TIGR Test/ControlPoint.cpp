#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif
#include "ControlPoint.h"


ControlPoint::ControlPoint(int x, int y, int width, Tigr* context)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->context = context;
}

void ControlPoint::Draw()
{
	tigrFill(context, x-width/2, y-width/2, width, width, tigrRGB(255, 0, 0));
}

bool ControlPoint::Intersects(int x, int y)
{
	return true;
}

Tigr* context;
int x = 0, y = 0;
int width;		
