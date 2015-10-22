/*
Order the 8 numbers puzzle (3x3) with BFS.
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <iomanip>
#include <string>

using namespace std;

int n = 3;
int goal[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
//int a[] = {6, 5, 3, 2, 4, 8, 7, 0, 1};
int a[] = {4, 5, 8, 3, 0, 1, 6, 2, 7};

//362880
int dist[362881];
int previous[362881];

int fact(int base)
{
	int p = 1;
	while(base > 1)
	{
		p*=base--;
	}
	return p;
}

int indexOfPermutation(int *arr, int size)  
{
	if(size == 0)  
	{  
		return 0; 
	}
	int i,k = 0;
	for(i = 1; i < size; i++)
	{
		k+= arr[i] < arr[0] ? 1 : 0;
	}

	return (k * fact(size-1)) + indexOfPermutation(arr + 1, size -1);   
}

int getDistance(int *state)
{
	int i = indexOfPermutation(state, n*n);
	return dist[i] - 1;
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

bool isValid(int x, int y)
{
	return 0 <= x && x < n && 0 <=y && y < n;
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

bool shouldGoThere(int *nextState)
{
	return getDistance(nextState) <= 0;
}

bool goalReachable(int *currentState)
{
	int inversions = 0;
	for (int i = 0; i < n*n; i++)
	{
		for (int j = i + 1; j < n * n; j++)
		{
			inversions += (currentState[j] && currentState[i] > currentState[j]) ? 1 : 0;
		}
	}
	return inversions % 2 == 0;
}

void getInput()
{
	for(int i = 0; i < n * n; i++)
	{
		cin>>a[i];
	}
}

void printPerm(int *perm)
{
	if(perm == NULL)
	{
		printf("None");
		return;
	}
	for (int i = 0; i < n*n; i++)
	{
		printf("%d,", perm[i]);
	}
}

void visit(int *currentState, int* prevState)
{
	int steps, prev = -1;
	int curr = indexOfPermutation(currentState, n*n);
	if(prevState == NULL)
	{
		steps = 1;
		previous[curr] = -1;
	}
	else
	{
		prev = indexOfPermutation(prevState, n*n);
		steps = dist[prev] + 1;
		previous[curr] = prev;
	}

	/* DEBUG PURPOSES */
	/*cout<<prev<<" from:";printPerm(prevState);cout<<endl;
	cout<<curr<<"   to:";printPerm(currentState);cout<<endl;
	cout<<endl;*/
	dist[curr] = steps;
}

int bfs(int *start)
{
	if(!goalReachable(start))
	{
		return -1;
	}

	int startX, startY;
	for (int i = 0; i < n*n; i++)
	{
		if(start[i] == 0)
		{
			startX = i % n;
			startY = i / n;
		}
	}
	
	int movex[] = {1,0,0,-1};
	int movey[] = {0,-1,1,0};

	queue<pair<int, int>> q;
	queue<int*> states;

	int *currentState = start;
	int *nextState;

	pair<int, int> k (startX,startY);
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
				int d = getDistance(nextState);
				//if(shouldGoThere(nextState))
				if(d < 0)
				{
					visit(nextState, currentState);
					q.push(make_pair(nextX, nextY));
					states.push(nextState);
				}
			}
		}
	}
	return -1;
}

/* DEBUG PURPOSES */
int* invertIndex(int index, int N)
{
	int* J = new int[N] ();
	int M = fact(N - 1);
	int k;

	for (k = 0; M > 1; k++)
	{
		J[k] = index / M;
		index = index % M;
		M /= --N;
	}
	J[k] = index;
	return J;
}
/* DEBUG PURPOSES */
int* permute(int index, int N)
{
	int* Jdx = invertIndex(index,N);
	int first = 0;
	int* Line = new int[N] ();

	int Limit;

	Line[0] = first;
	for (Limit = 1; Limit < N; Limit++)
	{
		Line[Limit] = (char)(1+Line[Limit-1]);
	}

	for (Limit = 0; Limit < N; Limit++)
	{
		int Hold;
		int Idx = Limit + Jdx[Limit];
		Hold = Line[Idx];
		while (Idx > Limit)
		{
			Line[Idx] = Line[Idx-1];
			Idx--;
		}
		Line[Idx] = Hold;
	}
	return Line;
}
/* DEBUG PURPOSES */
void printGraph()
{
	bool canGo = true;
	for (int i = 1; canGo;i++)
	{
		canGo = false;
		for (int j = 0; j < 362881; j++)
		{
			if(dist[j] == i)
			{
				canGo = true;
				string curr_str = "", prev_str = "";
				int *perm = permute(j, n*n);				
				for (int i = 0; i < 9; i++)
				{
					curr_str = curr_str + char(perm[i] + '0') + ",";
				}
				perm = permute(previous[j], n*n);
				for (int i = 0; i < 9; i++)
				{
					prev_str = prev_str + char(perm[i] + '0') + ",";
				}
				
				cout<<j<<" curr:"<<curr_str<<endl;
				cout<<previous[j]<<" prev:"<<prev_str<<endl;
				cout<<endl;
			}
		}
	}
}

int main()
{
	//getInput();
	int d = bfs(a);
	printf("%d\n", d);

	//printGraph();
	
	return 0;
}
