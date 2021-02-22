#include <iostream>
#include <fstream>
#include <string>

#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define FIRST_TEMP_OUT "1.txt"
#define SECOND_TEMP_OUT "2.txt"

int createOutputAndCountLines() {
    std::string sl;
    std::ifstream f(INPUT);
    std::ofstream f1(OUTPUT);
    int n = 0;
    while (!f.eof()) {
        getline(f, sl);
        if (sl != "")
            n++;
        f1 << sl << std::endl;
    }
    return n;
}

void split(int count) {
    std::ifstream f(OUTPUT);
    std::ofstream a(FIRST_TEMP_OUT);
    std::ofstream b(SECOND_TEMP_OUT);
    std::string line;
    getline(f, line);// считывание первой строки
    while (!f.eof()) {
        for (int i = 0 ; i < count && (!f.eof()) ; i++) {
            a << line << std::endl;
            getline(f,line);
        }
        for (int j = 0 ; j < count && !f.eof() ; j++) {
            b << line << std::endl;
            getline(f, line);
        }
    }

    a.close();
    b.close();
    f.close();
}

void merge(int count) {
    std::ifstream a(FIRST_TEMP_OUT);
    std::ifstream b(SECOND_TEMP_OUT);
    std::ofstream f(OUTPUT);
    std::string firstLine, secondLine;

    if (!a.eof())
        getline(a, firstLine);
    if (!b.eof())
        getline(b, secondLine);
    while (!a.eof() && !b.eof()) {
        int i = 0;
        int j = 0;
        while (i < count && j < count && !a.eof() && !b.eof()) {
            if (firstLine.length() < secondLine.length()) {
                f << firstLine << std::endl;
                getline(a, firstLine);
                i++;
            }
            else {
                f << secondLine << std::endl;
                getline(b, secondLine);
                j++;
            }
        }
        while (i < count && !a.eof()) {
            f << firstLine << std::endl;
            getline(a, firstLine);
            i++;
        }
        while (j < count && !b.eof()) { // дописываем ост. из файла b
            f << secondLine << std::endl;
            getline(b, secondLine);
            j++;
        }
    }
    while (!a.eof()) {
        f << firstLine << std::endl;
        getline(a, firstLine);
    }
    while (!b.eof()) {
        f << secondLine << std::endl;
        getline(b, secondLine);
    }
    a.close();
    b.close();
    f.close();
}

int main() {
    setlocale(0, "");
    int count = 1;
    int n = createOutputAndCountLines();
    std::cout << "Lines in file: " << n << std::endl;
    while (count < n) {
        split(count);
        merge(count);
        count *= 2;
    }
    remove(FIRST_TEMP_OUT);
    remove(SECOND_TEMP_OUT);

    return 0;
}