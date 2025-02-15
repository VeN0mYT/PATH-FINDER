#include<raylib.h>
#include<iostream>
#include"control.hpp"

int main()
{
	InitWindow(1600, 1000, "PATH FINDER");
	SetTargetFPS(60);
	
	CONTROLLER* control = new CONTROLLER(20,50,0);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		control->update();
		EndDrawing();
	}
	delete control;
	
	return 0;
}