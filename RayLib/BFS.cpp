#include "BFS.hpp"

void BFS::StartBFS(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex)
{
    parent.clear();
    while(!q.empty()) q.pop();

    count = 0;

    startTime = GetTime();
    elapsedTime = 0.0;

    parent.assign(cellCount, std::vector<Vector2>(cellCount, { -1, -1 }));
   

    parent[int(startindex.x)][int(startindex.y)] = { -2,-2 };
   
    q.push(startindex);
    running = true;
}

void BFS::BFSAlgo(CELL** cells, int cellCount, Vector2 startindex, Vector2 endindex,int stepsPerFrame,double delay)
{
    



    if (q.empty() || !running)
    {
        running = false;
        return;
    }

    double currentTime = GetTime(); 
    elapsedTime = currentTime - startTime;
    if (currentTime - Timer < delay) return; 

    Timer = currentTime;

    for (int step = 0; step < stepsPerFrame; step++)
    {
        if (q.empty())  
        {
            running = false;
            return;
        }

        Vector2 current = q.front();
        q.pop();

        if (int(current.x) == int(endindex.x) && int(current.y) == int(endindex.y))
        {
            std::cout << "Path found" << std::endl;
            ReconstructPath(cells, endindex, parent);
            running = false;
            elapsedTime = GetTime() - startTime;
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = int(current.x) + dx[i];
            int ny = int(current.y) + dy[i];

            if ((nx >= 0 && nx < cellCount && ny >= 0 && ny < cellCount) &&
                cells[nx][ny].type != cellType::WALL &&
                parent[nx][ny].x == -1)
            {
                q.push({ float(nx), float(ny) });
                parent[nx][ny] = current;

                if (cells[nx][ny].type != cellType::END && cells[nx][ny].type != cellType::START)
                {
                    cells[nx][ny].type = cellType::VISITED;
                }

            }
        }

    }
}

void BFS::ReconstructPath(CELL** cells, Vector2 endindex, const std::vector<std::vector<Vector2>>& parent)
{
    std::cout << "reconstruct" << std::endl;
    Vector2 current = endindex;

    while (int(current.x) != -1 && int(current.y) != -1)
    {
       
        

        int cx = int(current.x);
        int cy = int(current.y);
        if (cells[cx][cy].type != cellType::END && cells[cx][cy].type != cellType::START)
        {
            cells[cx][cy].type = cellType::PARANT;
            count++;
        }
        if (parent[cx][cy].x == -2 && parent[cx][cy].y == -2)
        {
            break;
        }

        current = parent[cx][cy];
    }
}


void BFS::DrawThings()
{
    
    DrawText("BFS TIME!!", 1100, 100, 60, WHITE);
    DrawText(TextFormat("%.2f sec",elapsedTime), 1100, 200, 60, WHITE);
    DrawText(TextFormat("cells num BFS -> %d",count), 1000, 300, 60, WHITE);
}
