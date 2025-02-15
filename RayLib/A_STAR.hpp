#pragma once
#include<raylib.h>
#include<iostream>
#include<queue>
#include<vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include"cell.hpp"
#include"grid.hpp"

struct Node {
	int x=0, y=0;
	int g = 0;
	int h = 0;
	int f = 0;
	Node* parent = NULL;
	Node(int _x, int _y, float _g, float _h, Node* _parent)
		: x(_x), y(_y), g(_g), h(_h), f(_g + _h), parent(_parent) {
	}
};

struct CompareNode {
	bool operator()(Node* a, Node* b) const {
		return a->f > b->f;
	}
};

inline float Heuristic(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

class A_STAR {
private:
	int dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1};
	std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
	std::unordered_map<int, Node*> visited;
	std::vector<Node*> path;
	bool running = false, found = false;
	float startTime = 0;
	float Timer = 0;
	float elapsedTime = 0.0;
	int counter = 0;
public:
	void StartAStar(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex);
	void AStarStep(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex, int stepsPerFrame, double delay);
	void DrawInfo();

	bool IsRunning() { return running; }
};