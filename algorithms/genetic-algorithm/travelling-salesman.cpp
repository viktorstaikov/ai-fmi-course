#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

string filename = "input.txt";

int N, POPULATION_SIZE;
vector<vector<int> > D;

struct Element {
    vector<int> towns;

    Element(vector<int> p)
    {
        towns = p;
    }

    int fitness()
    {
        int fitness = 0;

        int from, to;
        for (int i = 0; i < N; ++i) {
            from = i;
            to = (i + 1) % N;
            fitness += D[from][to];
        }
        return fitness;
    }

    void mutate(double probability)
    {
        double rand_num = ((double)rand() / (RAND_MAX));
        bool mutating = rand_num < probability;

        if (!mutating) {
            return;
        }

        int indexFrom = rand_num * towns.size();
        int indexTo = (1 - rand_num) * towns.size();

        swap(towns[indexFrom], towns[indexTo]);
    }
};

bool operator<(const Element& l, const Element& r)
{
    return l.fitness() < r.fitness();
}

Element crossover(const Element& male, const Element& female)
{
    vector<int> p;
    for (int i = 0; i < male.towns.size() / 2; ++i) {
        p.push_back(male.towns[i]);
    }
    vector<int>::iterator it;
    for (int i = 0; i < female.towns.size(); ++i) {
        it = find(p.begin(), p.end(), female.towns[i]);
        if (it != p.end()) {
            p.push_back(female.towns[i]);
        }
    }
    return Element(p);
}

void readInput()
{
    ifstream fin;
    fin.open(filename);
    fin >> N;
    int e;
    for (int i = 0; i < N; ++i) {
        vector<int> v;
        for (int j = 0; j < N; ++j) {
            fin >> e;
            v.push_back(e);
        }
        D.push_back(v);
    }
    fin >> POPULATION_SIZE;
}

void randomPopulation(int size, vector<Element>& v, priority_queue<Element> pq)
{
    int index;
    for (int i = 0; i < size; ++i) {
        vector<int> p;
        for (int j = 0; j < N; ++j) {
            p.push_back(j);
        }
        random_shuffle(p.begin(), p.end());
        v.push_back(Element(p));
        pq.push(v[i]);
    }
}

void solve(int iterations, double mutationProbability)
{
    vector<Element> v;
    priority_queue<Element> pq;

    int male, female;

    randomPopulation(POPULATION_SIZE, &v, &pq);

    while (iterations--) {
        male = rand() % POPULATION_SIZE;
        female = rand() % POPULATION_SIZE;
        Element child = crossover(v[male], v[female]);

        child.mutate(mutationProbability);

        if (child.fitness() > pq.front().fitness()) {
            pq.pop();
            pq.push(child);
        }
    }
}

int main()
{
    srand(time(NULL));

    readInput();

    return 0;
}