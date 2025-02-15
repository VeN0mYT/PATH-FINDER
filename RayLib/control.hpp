#pragma once
#include<raylib.h>
#include"grid.hpp"
#include"BFS.hpp"
#include"A_STAR.hpp"

class CONTROLLER
{
private:
	Vector2 startindex = { 0,0 };
	Vector2 endindex = { 0,0 };
	BFS* bfs;
	CELL** cell = NULL;
	GRID* grid;
	A_STAR* astar;
public:
	CONTROLLER(int cellSize, int cellCount, int offset)
	{ 
		grid = new GRID(cellSize, cellCount, offset);
		this->cell = grid->getCells();
		bfs = new BFS;
		astar = new A_STAR;
		std::cout << "CONTROLLER CREATED" << std::endl;

	}
	~CONTROLLER()
	{
		delete grid;
		delete bfs;
		delete astar;
		std::cout << "CONTROLLER DELETED" << std::endl;
	}
	void update();
	void resetCells(CELL** cells, int cellCount);
	void ChangeCell();
	Vector2 MousePos();
};