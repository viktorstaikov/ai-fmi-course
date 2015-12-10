/*


	For details regarding the task: iris.arff.txt


	% Summary Statistics:
	%  	               Min  Max   Mean    SD   Class Correlation
	%    sepal length: 4.3  7.9   5.84  0.83    0.7826   
	%     sepal width: 2.0  4.4   3.05  0.43   -0.4194
	%    petal length: 1.0  6.9   3.76  1.76    0.9490  (high!)
	%     petal width: 0.1  2.5   1.20  0.76    0.9565  (high!)
	% 
	% 9. Class Distribution: 33.3% for each of 3 classes.

	@RELATION iris

	@ATTRIBUTE sepallength	REAL
	@ATTRIBUTE sepalwidth 	REAL
	@ATTRIBUTE petallength 	REAL
	@ATTRIBUTE petalwidth	REAL
	@ATTRIBUTE class 	{Iris-setosa,Iris-versicolor,Iris-virginica}

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string input_data_file = "iris_train.txt";
string test_data_file = "iris_test.txt";
string expected_results_file = "iris_test_result.txt";

vector<vector<double> > input_data;
double min_value[] = { 4.3, 2.0, 1.0, 0.1 };
double max_value[] = { 7.9, 4.4, 6.9, 2.5 };

vector<vector<double> > test_data;
vector<double> expected_results;

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

        input_data.push_back(tokens);
        tokens.clear();
    }
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

        test_data.push_back(tokens);
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

int main()
{
    ReadInputData();
    ReadTestData();
    ReadExpectedResults();

    return 0;
}