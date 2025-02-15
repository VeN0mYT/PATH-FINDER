#pragma once
#include<raylib.h>
#include<iostream>
#include<queue>
#include<vector>
#include"cell.hpp"
#include"grid.hpp"

class BFS
{
private:
	int dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1};
	int count = 0;
	std::vector<std::vector<Vector2>> parent;
	std::queue<Vector2> q;
	bool running = false;
	double Timer = 0.0;
	double startTime = 0.0;
	double elapsedTime = 0.0;
	int counter = 0;
public:
	void StartBFS(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex);
	void BFSAlgo(CELL** cells, int cellCount,  Vector2 startindex, Vector2 endindex,int stepsPerFrame,double delay);
	void ReconstructPath(CELL** cells,Vector2 endindex, const std::vector<std::vector<Vector2>>& parent);
	void DrawThings();
	bool IsRunning() { return running; }
};