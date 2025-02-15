#include "control.hpp"



void CONTROLLER::update()
{
    ChangeCell();
	
	if (IsKeyPressed(KEY_SPACE)&&!bfs->IsRunning()&&!astar->IsRunning())
	{
		resetCells(cell, grid->getCellCount());
		bfs->StartBFS(cell, grid->getCellCount(), startindex, endindex);
		std::cout << "BFS worked" << std::endl;
	}
	if (IsKeyPressed(KEY_A) && !astar->IsRunning()&&!bfs->IsRunning())
	{
		resetCells(cell, grid->getCellCount());
		astar->StartAStar(grid->getCells(), grid->getCellCount(), startindex, endindex);
		std::cout << "A* worked" << std::endl;
	}
	bfs->BFSAlgo(grid->getCells(), grid->getCellCount(), startindex, endindex,5, 0.05);
	astar->AStarStep(grid->getCells(), grid->getCellCount(),startindex, endindex,5, 0.05);
	grid->draw();
	bfs->DrawThings();
	astar->DrawInfo();
}

void CONTROLLER::ChangeCell()
{
	if (IsKeyDown(KEY_V))
	{
		Vector2 pos = MousePos();
		int nx = pos.x;
		int ny = pos.y;
		if (nx != -2 && ny != -2&& cell[nx][ny].type != cellType::START && cell[nx][ny].type != cellType::END )
		{
			cell[nx][ny].type = cellType::UNVISITED;
		}

	}
	if (IsKeyDown(KEY_S))
	{
		Vector2 pos = MousePos();
		int nx = pos.x;
		int ny = pos.y;
		if (nx != -2 && ny != -2 && (cell[nx][ny].type != cellType::END))
		{
			cell[int(startindex.x)][int(startindex.y)].type = cellType::UNVISITED;
			cell[nx][ny].type = cellType::START;
			startindex = pos;
		}

	}
	if (IsKeyDown(KEY_E))
	{
		Vector2 pos = MousePos();
		int nx = pos.x;
		int ny = pos.y;
		if (nx != -2 && ny != -2 && (cell[nx][ny].type != cellType::START))
		{
			cell[int(endindex.x)][int(endindex.y)].type = cellType::UNVISITED;
			cell[nx][ny].type = cellType::END;
			endindex = pos;
		}

	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 pos = MousePos();
		int nx = pos.x;
		int ny = pos.y;
		if (nx != -2 && ny != -2 && cell[nx][ny].type != cellType::START && cell[nx][ny].type != cellType::END)
		{
			cell[nx][ny].type = cellType::WALL;
		}

	}
}

void CONTROLLER::resetCells(CELL** cells, int cellCount)
{
	for (int i = 0; i < cellCount; i++)
	{
		for (int j = 0; j < cellCount; j++)
		{
			if (cells[i][j].type != cellType::WALL && cells[i][j].type != cellType::START && cells[i][j].type != cellType::END)
			{
				cells[i][j].type = cellType::UNVISITED;
			}
		}
	}
}

Vector2 CONTROLLER::MousePos()
{
	Vector2 pos = GetMousePosition();
	pos.x = (pos.x - grid->getOffset()) / grid->getCellSize();
	pos.y = (pos.y - grid->getOffset()) / grid->getCellSize();
	if (pos.x >= 0 && pos.y >= 0 && pos.x < grid->getCellCount() && pos.y < grid->getCellCount())
	{
		return pos;
	}
	std::cout<<"Mouse out of range" << std::endl;
	return { -2,-2 };
}
