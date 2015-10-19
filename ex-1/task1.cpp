#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int n = 3;
int goal[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
int a[] = {6, 5, 3, 2, 4, 8, 7, 0, 1};
//int a[] = {1, 2, 3, 4, 5, 6, 7, 0, 8};
// power of 2
int dist[524288];

void getInput()
{
	for(int i = 0; i < n * n; i++)
	{
		cin>>a[i];
	}
}

int fact(int base)
{
	int p = 1;
	while(base > 1)
	{
		p*=base--;
	}
	return p;
}

int indexOf(int *arr, int size)  
{
	if(arr ==0 || *arr==0 || size == 0)  
	{  
		return 0; 
	}
	int i,k = 0;
	for(i = 1; i < size; i++)
	{
		k+= arr[i] < arr[0] ? 1 : 0;
	}

	return (k * fact(size-1)) + indexOf(arr + 1, size -1);   
}

bool isValid(int x, int y)
{
	return 0 <= x && x < n && 0 <=y && y < n;
}

int* getNextState(int *state, int oldx, int oldy, int nextx, int nexty)
{
	int *nextState = new int[n*n];
	int old = oldy*n + oldx;
	int next = nexty*n + nextx;
	for (int i = 0; i < n*n; i++)
	{
		nextState[i] = state[i];
	}
	nextState[old] = state[next];
	nextState[next] = state[old];
	return nextState;
}

int getDistance(int *state)
{
	int i = indexOf(state, n*n);
	return dist[i] - 1;
}

bool equalStates(int *source, int *target)
{
	for (int i = 0; i < n*n; i++)
	{
		if(source[i] != target[i])
		{
			return false;
		}
	}
	return true;
}

void visit(int *currentState, int* prevState)
{
	int steps;
	int curr = indexOf(currentState, n*n);
	if(prevState == NULL)
	{
		steps = 1;
	}
	else
	{
		int prev = indexOf(prevState, n*n);
		steps = dist[prev] + 1;
	}
	dist[curr] = steps;
}

bool isNotVisited(int *nextState)
{
	return getDistance(nextState) < 0;
}

int bfs(int *start, int *end)
{
	int startX, startY;
	for (int i = 0; i < n*n; i++)
	{
		if(start[i] == 0)
		{
			startX = i % n;
			startY = i / n;
		}
	}
	
	int movex[] = {1,0,-1,0};
	int movey[] = {0,1,0,-1};

	queue<pair<int, int>> q;
	queue<int*> states;

	pair<int, int> k (startX,startY);
	int *currentState = start;
	int *nextState;
	q.push(k);
	states.push(start);
	visit(start, NULL);

	while(!q.empty())
	{
		int nextX, nextY;

		k = q.front();
		q.pop();
		currentState = states.front();
		states.pop();
		
		if(equalStates(currentState, goal))
		{
			return getDistance(currentState);
		}

		for (int i = 0; i < 4; i++)
		{
			nextX = k.first + movex[i];
			nextY = k.second + movey[i];
			if(isValid(nextX, nextY))
			{
				nextState = getNextState(currentState, k.first, k.second, nextX, nextY);
				if(isNotVisited(nextState)) // from *start to *start the distance is always 0
				{
					q.push(make_pair(nextX, nextY));
					states.push(nextState);

					visit(nextState, currentState);
				}
			}
		}
		//delete currentState;
	}
	return 0;
}

int main()
{
	//getInput();
	int d = bfs(a, goal);
	printf("%d\n", d);
	return 0;
}

