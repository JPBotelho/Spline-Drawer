#pragma once
void GetScreenRes();

bool LMBdown(int bitmask);
bool MMBdown(int bitmask);
bool RMBdown(int bitmask);

bool OnMouseDown();
bool OnMouseStay();
bool OnMouseExit();

void GetPointAtCursor();
void UpdateMouse();
void DrawLines();
void DrawPoints();

