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

class Element {
public:
    vector<int> towns;
    int fitness;

    Element(vector<int> p)
    {
        this->towns = p;
        this->updateFitness();
    }

    void updateFitness()
    {
        int f = 0;

        int from, to;
        for (int i = 0; i < N; ++i) {
            from = this->towns[i];
            to = this->towns[(i + 1) % N];
            f += D[from][to];
        }
        this->fitness = f;
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

        this->updateFitness();
    }
};

bool operator<(const Element& l, const Element& r)
{
    return l.fitness < r.fitness;
}

Element crossover(const Element& male, const Element& female)
{
    vector<int> p;
    for (int i = 0; i < male.towns.size() / 2; ++i) {
        p.push_back(male.towns[i]);
    }

    for (int i = 0; i < female.towns.size(); ++i) {
        bool contains = false;
        for (int j = 0; j < p.size(); j++) {
            contains |= female.towns[i] == p[j];
        }
        if (!contains)
            p.push_back(female.towns[i]);
    }
    auto e = Element(p);
    return e;
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

void randomPopulation(int size, vector<Element>& v, priority_queue<Element>& pq)
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
    int i = 0;

    randomPopulation(POPULATION_SIZE, v, pq);

    while (i < iterations) {
        i++;

        male = rand() % POPULATION_SIZE;
        female = rand() % POPULATION_SIZE;

        Element child = crossover(v[male], v[female]);

        child.mutate(mutationProbability);

        Element leastFit = pq.top();
        if (child.fitness > leastFit.fitness) {
            pq.pop();
            // substitute the elements
            leastFit.towns = child.towns;
            leastFit.fitness = child.fitness;
            pq.push(leastFit);
        }
    }

    Element best = pq.top();
    pq.pop();
    while (!pq.empty()) {
        best = pq.top();
        pq.pop();
    }
    cout << best.fitness << endl;
}

int main()
{
    srand(time(NULL));

    readInput();
    solve(1000000, 0.1);
    return 0;
}