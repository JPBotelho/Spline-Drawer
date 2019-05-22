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
		ControlPoint(float x, float y, float width, Tigr* context);
		void Draw();
		bool Intersects(int x, int y);
		float x, y, width;
		int screenX;
		int screenY;	
};