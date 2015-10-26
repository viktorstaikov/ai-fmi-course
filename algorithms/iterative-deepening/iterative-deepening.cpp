#include <cstdio>

using namespace std;

int N = 7;
int M = 10;
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
int *visited;

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

void visit(int x, int y)
{
	visited[x + N*y] = 1;
}

bool dls(int startX, int startY, int endX, int endY, int depth)
{
	if (startY == endY && startX == endX)
	{
		return true;
	}
	if(depth == 0)
	{
		return false;
	}
	visit(startX, startY);

	int nextX, nextY;
	for (int i = 0; i < 4; ++i)
	{
		nextX = startX + movex[i];
		nextY = startY + movey[i];

		if(isValid(nextX, nextY))
		{
			if(!isVisited(nextX, nextY))
			{
				if(dls(nextX, nextY, endX, endY, depth - 1))
				{
					printf("(%d, %d)\n", nextX, nextY);
					return true;
				}
			}
		}
	}
	return false;
}


int iterativeDeepening(int startX, int startY, int endX, int endY)
{
	for (int i = 0; i < N*M; ++i)
	{
		init();
		if(dls(startX, startY, endX, endY, i))
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	int startX = 0;
	int startY = 0;
	int endX = 3;
	int endY = 6;

	int d = iterativeDeepening(startX, startY, endX, endY);
	printf("%d\n", d);
	return 0;
}