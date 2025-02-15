#pragma once
#include<raylib.h>

enum class cellType {
  VISITED,
  UNVISITED,
  WALL,
  START,
  END,
  PARANT
};

struct CELL {
  cellType type;
  Vector2 pos;
  CELL()
  {
	  type = cellType::UNVISITED;
	  pos = { 0,0 };
  }
};


