#include <cstdio>
#include <queue>

using namespace std;

int N = 7;
int M = 10;
int *dist = new int[N*M]();
int a[][10] = {                     // x
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
  	{0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 3
  	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // 2
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 0
 /*y 0  1  2  3  4  5  6  7  8  9 */ 
};
int movex[] = {-1, 0, 1, 0};
int movey[] = {0, -1, 0, 1};


void init()
{
	for (int i = 0; i < N*M; ++i)
	{
		dist[i] = 0;
	}
}

bool isValid(int x, int y)
{
	return 0 <= x && x < N && 0 <= y && y < M  && a[x][y] == 0;
}

bool isVisited(int x,int y)
{
	return dist[x + N*y];
}

void visit(int x, int y, int prevX, int prevY)
{
	dist[x + N*y] = dist[prevX + N*prevY] + 1;
}

int getDistance(int x, int y)
{
	return dist[x + N*y] - 1;
}

int bfs(int startX, int startY, int endX, int endY)
{
	if(startX == endX && startY == endY)
	{
		return 0;
	}

	queue<int> qx, qy;
	int currentX, currentY, nextX, nextY;
	qx.push(startX);
	qy.push(startY);

	visit(startX,startY, startX, startY);
	
	while(!qx.empty())
	{
		currentX = qx.front(); qx.pop();
		currentY = qy.front(); qy.pop();

		for (int i = 0; i < 4; ++i)
		{
			nextX = currentX + movex[i];
			nextY = currentY + movey[i];

			if(isValid(nextX,nextY))
			{
				if(!isVisited(nextX, nextY))
				{
					visit(nextX, nextY, currentX, currentY);
					qx.push(nextX);
					qy.push(nextY);
				}
			}
		}
	}

	return getDistance(endX, endY);
}

bool _dfs(int startX, int startY, int endX, int endY)
{
	if(startX == endX && startY == endY)
	{
		return true;
	}

	int nextX, nextY;
	for (int i = 0; i < 4; ++i)
	{
		nextX = startX + movex[i];
		nextY = startY + movey[i];

		if(isValid(nextX, nextY))
		{
			if(!isVisited(nextX, nextY))
			{
				visit(nextX, nextY, startX, startY);
				if(_dfs(nextX, nextY, endX, endY))
				{
					printf("(%d, %d)\n", nextX, nextY);
					return true;
				}
			}
		}
	}
	return false;
}

int dfs(int startX, int startY, int endX, int endY)
{
	visit(startX, startY, startX, startY);
	_dfs(startX, startY, endX, endY);
	return getDistance(endX, endY);
}

int main()
{
	init();
	int startX = 0;
	int startY = 0;
	int endX = 3;
	int endY = 6;

	int d = dfs(startY, startY, endX, endY);
	printf("%d\n", d);

	init();
	d = bfs(startX, startY, endX, endY);
	printf("%d\n", d);
	return 0;
}