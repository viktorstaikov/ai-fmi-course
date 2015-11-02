#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;

struct Cell
{
	int x, y;
	int heuristics, dist;
	Cell(int x, int y, int h = 0, int d = 0) : x(x), y(y), heuristics(h), dist(d)
	{}
};
Cell make_cell(int x, int y, int h = 0, int d = 0)
{
	return Cell(x,y,h,d);
}
/* the operator MUST BE REVERSED for finding the minimal path */
bool operator<(const Cell & l, const Cell & r)
{
	return l.heuristics + l.dist > r.heuristics + r.dist;
}

int N = 7;
int M = 10;
int *visited;
int a[][10] = {                     // x
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
  	{0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 3
  	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // 4
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 6
 /*y 0  1  2  3  4  5  6  7  8  9 */ 
};
int movex[] = {-1, 0, 1, 0};
int movey[] = {0, -1, 0, 1};

void init()
{
	if(visited) delete visited;
	visited = new int[N*M]();
}

bool isValid(int x, int y)
{
	return 0 <= x && x < N && 0 <= y && y < M  && a[x][y] == 0;
}

bool isVisited(int x,int y)
{
	return visited[x + N*y];
}

void visit(int x, int y, int dist)
{
	visited[x + N*y] = dist;
}

int heuristic(int x, int y, int endX, int endY)
{
	return abs(x - endX) + abs(y - endY);
}

int a_star(int startX, int startY, int endX, int endY)
{
	priority_queue<Cell> pq;
	Cell current(0,0);
	int nextX, nextY;
	visit(startX, startY, 1);

	pq.push(make_cell(startX, startY, heuristic(startX, startY, endX, endY), 1));

	while(!pq.empty())
	{
		current = pq.top(); pq.pop();

		// printf("--- %d, %d\n", current.x, current.y);

		for (int i = 0; i < 4; ++i)
		{
			nextX = current.x + movex[i];
			nextY = current.y + movey[i];

			if(isValid(nextX, nextY))
			{
				if(!isVisited(nextX, nextY))
				{
					visit(nextX, nextY, current.dist + 1);
					pq.push(make_cell(nextX, nextY, heuristic(nextX, nextY, endX, endY), current.dist + 1));
					// printf("pushing %d, %d\n", nextX, nextY);
				}
			}
		}
	}

	return visited[endX + N*endY] - 1;
}

int main()
{
	init();

	int startX = 3;
	int startY = 6;
	int endX = 5;
	int endY = 4;
	int d = a_star(startX, startY, endX, endY);
	printf("%d\n", d);

	return 0;
}