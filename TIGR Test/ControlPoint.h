#pragma once

#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif

class ControlPoint
{
	public:
		ControlPoint();
		Tigr* context;
		ControlPoint(int x, int y, int width, Tigr* context);
		void Draw();
		bool Intersects(int x, int y);
		int x, y, width;
};