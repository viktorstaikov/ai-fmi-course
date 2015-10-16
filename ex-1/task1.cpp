#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int n = 3;
int goal[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
int a[9];

void getInput()
{
	int i, j;
	for(i = 0; i < n * n; i++)
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

int index(int *arr, int size)  
{
	if(arr ==0 || *arr==0 || size == 0)  
	{  
		return 0; 
	}
	int i,k=0;
	for(i = 1; i < size; i++)
	{
		k+= arr[i] < arr[0] ? 1 : 0;
	}

	return (k * fact(size-1)) + index(arr + 1, size -1);   
}

int bfs(int *start, int *end)
{
	queue<int*> q;
	q.push(start);
	int *k;

	while(!q.emplace())
	{
		k = q.front();
		q.pop();

	}
}

int main()
{
	//getInput();
	a = {6, 5, 3, 2, 4, 8, 7, 0, 1};
	
	return 0;
}

