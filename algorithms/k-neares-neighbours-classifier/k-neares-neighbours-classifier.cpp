/*


    For details regarding the task: iris.arff.txt


    % Summary Statistics:
    %                  Min  Max   Mean    SD   Class Correlation
    %    sepal length: 4.3  7.9   5.84  0.83    0.7826   
    %     sepal width: 2.0  4.4   3.05  0.43   -0.4194
    %    petal length: 1.0  6.9   3.76  1.76    0.9490  (high!)
    %     petal width: 0.1  2.5   1.20  0.76    0.9565  (high!)
    % 
    % 9. Class Distribution: 33.3% for each of 3 classes.

    @RELATION iris

    @ATTRIBUTE sepallength  REAL
    @ATTRIBUTE sepalwidth   REAL
    @ATTRIBUTE petallength  REAL
    @ATTRIBUTE petalwidth   REAL
    @ATTRIBUTE class    {Iris-setosa,Iris-versicolor,Iris-virginica}

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <queue>

using namespace std;

int K = 15;

string input_data_file = "iris_train.txt";
string test_data_file = "iris_test.txt";
string expected_results_file = "iris_test_result.txt";

struct IrisPlant {
    double sepallength, sepalwidth, petallength, petalwidth;
    int cl;
    IrisPlant()
    {
        IrisPlant(0, 0, 0, 0);
    }

    IrisPlant(double sl, double sw, double pl, double pw, double cl = -1)
        : sepallength(sl)
        , sepalwidth(sw)
        , petallength(pl)
        , petalwidth(pw)
        , cl(cl)
    {
    }
};

vector<IrisPlant> input_data;
vector<IrisPlant> test_data;
vector<double> expected_results;

IrisPlant max_value = IrisPlant(7.9, 4.4, 6.9, 2.5);
IrisPlant min_value = IrisPlant(4.3, 2.0, 1.0, 0.1);
IrisPlant value_range = IrisPlant(3.6, 2.4, 5.9, 2.4);

void ReadInputData()
{
    ifstream infile(input_data_file);
    string line;

    vector<double> tokens;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(stod(token));
        }

        input_data.push_back(IrisPlant(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]));
        tokens.clear();
    }
    random_shuffle(input_data.begin(), input_data.end());
    cout << "input data read" << endl;
}

void ReadTestData()
{
    ifstream infile(test_data_file);
    string line;

    vector<double> tokens;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(stod(token));
        }

        test_data.push_back(IrisPlant(tokens[0], tokens[1], tokens[2], tokens[3]));
        tokens.clear();
    }
    cout << "test data read" << endl;
}

void ReadExpectedResults()
{
    ifstream infile(expected_results_file);
    string line;

    while (getline(infile, line)) {
        expected_results.push_back(stod(line));
    }
    cout << "expected results read" << endl;
}

void SplitTheInputData()
{
    test_data = vector<IrisPlant>(input_data.begin() + input_data.size() / 2, input_data.end());
    input_data.erase(input_data.begin() + input_data.size() / 2, input_data.end());

    for (int i = 0; i < test_data.size(); i++) {
        expected_results.push_back(test_data[i].cl);
    }
}

double Distance(const IrisPlant& a, const IrisPlant& b)
{
    double d = 0;
    // d += fabs(a.sepallength - b.sepallength) / value_range.sepallength;
    // d += fabs(a.sepalwidth - b.sepalwidth) / value_range.sepalwidth;
    // d += fabs(a.petallength - b.petallength) / value_range.petallength;
    // d += fabs(a.petalwidth - b.petalwidth) / value_range.petalwidth;

    d += (a.sepallength - b.sepallength) * (a.sepallength - b.sepallength);
    d += (a.sepalwidth - b.sepalwidth) * (a.sepalwidth - b.sepalwidth);
    d += (a.petallength - b.petallength) * (a.petallength - b.petallength);
    d += (a.petalwidth - b.petalwidth) * (a.petalwidth - b.petalwidth);
    return sqrt(d);
}

bool operator<(const pair<double, IrisPlant>& l, const pair<double, IrisPlant>& r)
{
    return l.first < r.first;
}

vector<pair<double, IrisPlant> > GetKNearesNeighbours(const IrisPlant& plant, int k)
{
    //keep the farest element on top
    priority_queue<pair<double, IrisPlant> > pq;
    pair<double, IrisPlant> top;

    vector<pair<double, IrisPlant> > v;

    int i, sz = input_data.size();
    int limit = min(k, sz);
    double d = 0;
    IrisPlant tmp;
    for (i = 0; i < limit; i++) {
        d = Distance(plant, input_data[i]);
        pq.push(make_pair(d, input_data[i]));
    }
    for (i = limit; i < sz; i++) {
        tmp = input_data[i];
        top = pq.top();
        d = Distance(plant, tmp);

        if (d < top.first) {
            pq.pop();
            pq.push(make_pair(d, tmp));
        }
    }

    while (!pq.empty()) {
        v.push_back(pq.top());
        pq.pop();
    }
    return v;
}

int main()
{
    ReadInputData();
    ReadTestData();
    ReadExpectedResults();
    
    vector<pair<double, IrisPlant> > nearest;
    int classes[] = { 0, 0, 0, 0 };

    cout<<"my|expected|match\n";

    for (int i = 0; i < test_data.size(); i++) {
        nearest = GetKNearesNeighbours(test_data[i], K);

        for (int j = 0; j < nearest.size(); j++) {
            classes[nearest[j].second.cl]++;
        }

        test_data[i].cl = 1;
        int count = classes[1];
        for (int j = 2; j <= 3; j++) {
            if (count < classes[j]) {
                test_data[i].cl = j;
                count = classes[j];
            }
        }
        cout << test_data[i].cl << "|" << expected_results[i] << "|"  << (test_data[i].cl == expected_results[i]) << endl;
    }

    return 0;
}