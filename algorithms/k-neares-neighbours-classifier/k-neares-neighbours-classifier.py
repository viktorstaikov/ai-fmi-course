
# For details regarding the task: iris.arff.txt

# % Summary Statistics:
# %                  Min  Max   Mean    SD   Class Correlation
# %    sepal length: 4.3  7.9   5.84  0.83    0.7826
# %     sepal width: 2.0  4.4   3.05  0.43   -0.4194
# %    petal length: 1.0  6.9   3.76  1.76    0.9490  (high!)
# %     petal width: 0.1  2.5   1.20  0.76    0.9565  (high!)
# %
# % 9. Class Distribution: 33.3% for each of 3 classes.

# @RELATION iris

# @ATTRIBUTE sepallength  REAL
# @ATTRIBUTE sepalwidth   REAL
# @ATTRIBUTE petallength  REAL
# @ATTRIBUTE petalwidth   REAL
# @ATTRIBUTE class    {Iris-setosa,Iris-versicolor,Iris-virginica}


import csv
import random
import math
import operator

input_data_file = "iris_train.txt"
test_data_file = "iris_test.txt"
expected_results_file = "iris_test_result.txt"

K = 15

input_data = []
test_data = []
expected_data = []

max_value = [7.9, 4.4, 6.9, 2.5]
min_value = [4.3, 2.0, 1.0, 0.1]
value_range = [3.6, 2.4, 5.9, 2.4]


def LoadDataset(filename, data=[],):
    with open(filename, 'rb') as csvfile:
        lines = csv.reader(csvfile)
        dataset = list(lines)
        for x in range(len(dataset) - 1):
            for y in range(len(dataset[x])):
                dataset[x][y] = float(dataset[x][y])
            data.append(dataset[x])


def Distance(a, b, length=4):
    d = 0
    for x in range(length):
        d += abs(a[x] - b[x]) / value_range[x]
    return d


def GetNeighbours(instance, k):
    distances = []
    for x in range(len(input_data)):
        dist = Distance(instance, input_data[x])
        distances.append((input_data[x], dist))

    distances.sort(key=operator.itemgetter(1))
    neighbours = []
    for x in range(k):
        neighbours.append(distances[x][0])
    return neighbours


def Determine(neighbours):
    classVotes = {}
    for x in range(len(neighbours)):
        response = neighbours[x][-1]
        if response in classVotes:
            classVotes[response] += 1
        else:
            classVotes[response] = 1
    sortedVotes = sorted(classVotes.iteritems(),
                         key=operator.itemgetter(1), reverse=True)
    return sortedVotes[0][0]


def main():
    LoadDataset(input_data_file, input_data)
    LoadDataset(test_data_file, test_data)
    LoadDataset(expected_results_file, expected_data)

    for x in range(len(test_data)):
        neighbours = GetNeighbours(test_data[x], K)
        cl = Determine(neighbours)
        print(str(cl) + " " + str(expected_data[x][0]))


if __name__ == "__main__":
    main()
