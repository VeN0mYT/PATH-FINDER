#include "A_STAR.hpp"

void A_STAR::StartAStar(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex) {
    openList = {};
    visited.clear();
    path.clear();
    found = false;
    running = true;
    counter = 0;

    startTime = GetTime();
    Timer = startTime;
    elapsedTime = 0.0;

    Node* startNode = new Node(startindex.x, startindex.y, 0, Heuristic(startindex.x, startindex.y, endindex.x, endindex.y), nullptr);
    openList.push(startNode);
    visited[startindex.y * cellCount + startindex.x] = startNode;
}

void A_STAR::AStarStep(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex, int stepsPerFrame, double delay) {
    if (!running || found || openList.empty()) {
        running = false;
        return;
    }

    double currentTime = GetTime();
    if (!found) elapsedTime = currentTime - startTime;
    if (currentTime - Timer < delay) return;

    Timer = currentTime;

    for (int step = 0; step < stepsPerFrame; step++) {
        if (openList.empty()) {
            running = false;
            return;
        }

        Node* currentNode = openList.top();
        openList.pop();

        if (int(currentNode->x) == int(endindex.x) && int(currentNode->y) == int(endindex.y)) {
            while (currentNode != nullptr) {
                path.push_back(currentNode);
                if (cells[currentNode->x][currentNode->y].type != cellType::START && cells[currentNode->x][currentNode->y].type != cellType::END)
                {
                    cells[currentNode->x][currentNode->y].type = cellType::PARANT;
                    counter++;
                }
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(), path.end()); 
            found = true;
            running = false;  
            elapsedTime = GetTime() - startTime;  
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = currentNode->x + dx[i];
            int ny = currentNode->y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < cellCount && ny < cellCount && cells[nx][ny].type != cellType::WALL) {
                int newG = currentNode->g + 1;
                if (visited.find(ny * cellCount + nx) == visited.end() || newG < visited[ny * cellCount + nx]->g) {
                    Node* newNode = new Node(nx, ny, newG, Heuristic(nx, ny, endindex.x, endindex.y), currentNode);
                    visited[ny * cellCount + nx] = newNode;
                    if (cells[nx][ny].type != cellType::START && cells[nx][ny].type != cellType::END)
                    {
                        cells[nx][ny].type = cellType::VISITED;
                    }
                    openList.push(newNode);
                }
            }
        }
    }
}


void A_STAR::DrawInfo() {
    DrawText("A* SEARCH!", 1100, 600, 60, WHITE);
    DrawText(TextFormat("%.2f sec", elapsedTime), 1100, 700, 60, WHITE);
    DrawText(TextFormat("cells num A* -> %d", counter), 1000, 800, 60, WHITE);
}
