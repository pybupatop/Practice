#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define SENTENCE_DELIMETERS ".,!?@#$%^&*()[]{}-+_=~`\"<>;:\\/\n«»"
#define MAX_COLLOCATION_SIZE 5
#define INPUT "input.txt"

std::vector<std::string> split(std::string line, std::string delimeters) {
    std::vector<std::string> result;

    size_t pos = 0, prev = 0;

    while ((pos = line.find_first_of(delimeters.c_str(), prev)) != std::string::npos) {
        if (pos > prev)
            result.push_back(line.substr(prev, pos - prev));
        prev = pos + 1;
    }
    if (prev < line.length())
        result.push_back(line.substr(prev, std::string::npos));

    return result;
}

int main() {
    std::map<std::string, int> collocations;
    std::fstream input(INPUT, std::ios::in);
    std::vector<std::string> sentences;
    std::string line;
    while (getline(input, line)) {
        std::vector<std::string> sentence = split(line, SENTENCE_DELIMETERS);
        sentences.insert(sentences.end(), sentence.begin(), sentence.end());
    }
    std::vector<std::string> all_collocations;
    for (auto sentence: sentences) {
        std::vector<std::string> words = split(sentence, " ");
        for (int i = 0 ; i < words.size() - 1 ; i++) {
            std::string current_collocation = words[i];
            for (int j = i + 1 ; j < std::min((int) words.size(), i + MAX_COLLOCATION_SIZE) ; j++) {
                current_collocation += " " + words[j];
                all_collocations.push_back(current_collocation);
            }
        }
    }
    for (auto collocation: all_collocations) {
        collocations[collocation] += 1;
    }
    for (auto collocationStat: collocations) {
        if (collocationStat.second >= 2)
        {
            std::cout << collocationStat.first << ": " << collocationStat.second << std::endl;
        }
    }
}
