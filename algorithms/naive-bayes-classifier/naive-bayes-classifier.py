
# Moodle Task 7

# Attributes: sex, height (feet), weight (lbs), foot size(inches)


import csv

input_data_file = "input_data.txt"
test_data_file = "test_data.txt"

input_data = []
averages = []
test_data = []

classes = [0, 1]
classsesToStr = ["male", "female"]


def LoadDataset(filename, data=[],):
    with open(filename, 'rb') as csvfile:
        lines = csv.reader(csvfile)
        dataset = list(lines)
        for x in range(len(dataset)):
            for y in range(len(dataset[x])):
                dataset[x][y] = float(dataset[x][y])
            data.append(dataset[x])


def LoadInputData():
    with open(input_data_file, 'rb') as csvfile:
        lines = csv.reader(csvfile)
        dataset = list(lines)

        for x in range(len(dataset)):
            for y in range(len(dataset[x]) - 1):
                dataset[x][y] = float(dataset[x][y])
                if y >= len(averages):
                    averages.append(0)
                averages[y] += dataset[x][y]

            dataset[x][-1] = int(dataset[x][-1])
            input_data.append(dataset[x])

    length = len(input_data)
    for x in range(len(averages)):
        averages[x] /= length


def cond(x, y):
    return x > y


def Probability(h, D):
    count_h = len(filter(lambda x: x[-1] == h, input_data))

    total = 0.0
    used = 0.0

    prob = 1
    print(str(prob))
    for attr in range(len(D)):
        total += 1
        numerator = float(len(filter(
            lambda x: x[-1] == h and D[attr] == cond(averages[attr], x[attr]), input_data)))
        numerator /= count_h

        if numerator > 0:
            print(str(numerator))
            used += 1
            prob *= numerator

    prob *= used / total
    return prob


def main():
    # LoadDataset(input_data_file, input_data)
    LoadInputData()
    LoadDataset(test_data_file, test_data)

    for k in range(len(test_data)):
        t = test_data[k]
        D = [True] * len(t)
        for i in range(len(t)):
            D[i] = cond(averages[i], t[i])

        max_probability = 0
        current_probability = 0
        most_probable_class = -1
        for h in range(len(classes)):
            current_probability = Probability(h, D)
            print(current_probability)
            if max_probability < current_probability:
                max_probability = current_probability
                most_probable_class = h

        print("The most probable sex is " +
              classsesToStr[most_probable_class])

if __name__ == "__main__":
    main()
