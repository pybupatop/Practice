#include <iostream>
#include <fstream>
#include <sstream>

#define OUT1 "out1"
#define OUT2 "out2"

std::string getn_word(std::string input, int n) {
    std::stringstream s(input);
    std::string word;

    while (n > 0 && s >> word)
        n--;

    return word;
}

int split(std::ifstream &input, std::ofstream &out1, std::ofstream &out2, int n) {
    std::string line, prev_line, parameter, prev_parameter;
    std::ofstream *out[2] = {&out1, &out2};
    int out_index = 0;

    getline(input, prev_line);
    prev_parameter = getn_word(prev_line, n);

    while (input) {
        getline(input, line);
        parameter = getn_word(line, n);

        *out[out_index % 2] << prev_line << std::endl;

        if (parameter < prev_parameter)
            out_index++;

        prev_parameter = parameter;
        prev_line = line;
    }

    return out_index;
}

int split(std::string filename, int n) {
    std::ifstream input(filename.c_str());
    std::ofstream out1(OUT1), out2(OUT2);

    return split(input, out1, out2, n);
}

void merge(std::ofstream &out, std::ifstream &input1, std::ifstream &input2, int n) {
    std::string line1, line2, parameter1, parameter2;

    getline(input1, line1);
    getline(input2, line2);

    parameter1 = getn_word(line1, n);
    parameter2 = getn_word(line2, n);

    while (input1 || input2) {
        if ((parameter1 < parameter2 || parameter2.empty()) && !parameter1.empty()) {
            out << line1 << std::endl;
            getline(input1, line1);
            parameter1 = getn_word(line1, n);
        }
        else
            if ((parameter2 <= parameter1 || parameter1.empty()) && !parameter2.empty()) {
            out << line2 << std::endl;
            getline(input2, line2);
            parameter2 = getn_word(line2, n);
        }
        else
            break;
    }
}

void merge(std::string filename, int n) {
    std::ofstream out(filename.c_str());
    std::ifstream input1(OUT1), input2(OUT2);

    merge(out, input1, input2, n);
}

void natural_external_sort(std::string filename, int n) {
    while (split(filename, n) > 1)
        merge(filename, n);
    remove(OUT1);
    remove(OUT2);
}

int main() {
    int fieldNumber;
    std::string filename;
    std::cout << "Enter filename: "; std::cin >> filename;
    std::cout << "Enter number of field the file should be sorted by: ";
    std::cin >> fieldNumber;

    natural_external_sort(filename, fieldNumber);

    return 0;
}