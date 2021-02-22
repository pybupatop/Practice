#include <iostream>
#include <fstream>
#include <sstream>

#define OUT1 "out1"
#define OUT2 "out2"

std::string getName(std::string input) {
    std::stringstream ss(input);
    std::string word;

    ss >> word;

    return word;
}

int split(std::ifstream &input, std::ofstream &out1, std::ofstream &out2) {
    std::string line, prevLine, name, prevName;
    std::ofstream *out[2] = {&out1, &out2};
    int runNumber = 0;

    getline(input, prevLine);
    prevName = getName(prevLine);

    while (input) {
        getline(input, line);
        name = getName(line);

        *out[runNumber % 2] << prevLine << std::endl;

        if (name < prevName)
            runNumber++;

        prevName = name;
        prevLine = line;
    }

    return runNumber;
}

int split(std::string filename) {
    std::ifstream input(filename.c_str());
    std::ofstream out1(OUT1), out2(OUT2);

    return split(input, out1, out2);
}

void merge(std::ofstream &out, std::ifstream &input1, std::ifstream &input2) {
    std::string firstLine, secondLine, firstName, secondName;

    getline(input1, firstLine);
    getline(input2, secondLine);

    firstName = getName(firstLine);
    secondName = getName(secondLine);

    while (input1 || input2) {
        if ((firstName < secondName || secondName.empty()) && !firstName.empty()) {
            out << firstLine << std::endl;
            getline(input1, firstLine);
            firstName = getName(firstLine);
        }
        else if ((secondName <= firstName || firstName.empty()) && !secondName.empty()) {
            out << secondLine << std::endl;
            getline(input2, secondLine);
            secondName = getName(secondLine);
        }
        else
            break;
    }
}

void merge(std::string filename) {
    std::ofstream out(filename.c_str());
    std::ifstream input1(OUT1), input2(OUT2);

    merge(out, input1, input2);
}

void naturalExternalSort(std::string filename) {
    while (split(filename) > 1)
        merge(filename);
    remove(OUT1);
    remove(OUT2);
}

int main(int argc, char **argv) {
    std::string filename("input");
    naturalExternalSort(filename);
    return 0;
}