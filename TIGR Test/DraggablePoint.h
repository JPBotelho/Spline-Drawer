#pragma once

#include "tigr.h"
#ifdef _MSC_VER
#pragma comment(lib,"D3D9.lib")
#endif

class DraggablePoint
{
	public:
		DraggablePoint();
		Tigr* context;
		DraggablePoint(float x, float y, float width, Tigr* context);
		void Draw();
		bool Intersects(float x, float y);
		float x, y, width;
		int screenX;
		int screenY;	
};