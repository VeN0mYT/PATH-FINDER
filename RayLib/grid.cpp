#include "grid.hpp"

GRID::GRID(int cellSize, int cellCount, int offset)
{
	this->cellSize = cellSize;
	this->cellCount = cellCount;
	this->offset = offset;

	cells = new CELL * [cellCount];
	for (int i = 0; i < cellCount; i++)
	{
		cells[i] = new CELL[cellCount];
	}
	initGrid();
	std::cout << "grid initialized" << std::endl;
	
}

GRID::~GRID()
{
	for (int i = 0; i < cellCount; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
	std::cout << "grid deleted" << std::endl;
}

void GRID::initGrid()
{
	for (int i = 0; i < cellCount; i++)
	{
		for (int j = 0; j < cellCount; j++)
		{
			cells[i][j].type = cellType::UNVISITED;
			cells[i][j].pos = { float(i*cellSize+offset),float(j*cellSize+offset) };
		}
	}
}

void GRID::draw()
{
	cellType type;
	Color color;
	for (int i = 0; i < cellCount; i++)
	{
		for (int j = 0; j < cellCount; j++)
		{
			type = cells[i][j].type;
			switch (type)
			{
			case cellType::UNVISITED:
				color = GRAY;
				break;
			case cellType::VISITED:
				color = BLUE;
				break;
			case cellType::WALL:
				color = WHITE;
				break;
			case cellType::START:
				color = GREEN;
				break;
			case cellType::END:
				color = RED;
				break;
			case cellType::PARANT:
				color = YELLOW;
				break;
			default:
			    color = BLACK;
				break;
			}
			//DrawRectangle(cellSize * i+offset, cellSize * j+offset, cellSize, cellSize, color);
			DrawRectangle(cells[i][j].pos.x, cells[i][j].pos.y, cellSize, cellSize, color);
		}
	}

	for (int i = 0;i < cellCount;i++)
	{
		DrawLine(cellSize * i+offset, offset, cellSize * i+offset, cellSize * cellCount+offset, BLACK);
		DrawLine(offset, cellSize * i+offset, cellSize * cellCount+offset, cellSize * i+offset, BLACK);
	}
}
