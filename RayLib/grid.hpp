#pragma once
#include<raylib.h>
#include<iostream>
#include"cell.hpp"

class GRID
{
private:
	int cellSize=0;
	int cellCount=0;
	int offset=0;
	CELL **cells;

public:
	GRID(int cellSize, int cellCount, int offset);
	~GRID();
	void initGrid();

	void draw();

	CELL** getCells() { return cells; }
	int getCellSize() { return cellSize; }
	int getCellCount() { return cellCount; }
	int getOffset() { return offset; }
};