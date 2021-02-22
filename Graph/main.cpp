#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int pointCount, wireCount;
    std::cin >> pointCount >> wireCount;

    std::vector<std::vector<int>> connectionsFirst(pointCount);
    std::vector<std::vector<int>> connectionsSecond(pointCount);
    std::vector<int> D2(pointCount, 0);
    std::vector<int> D1(pointCount, 0);

    for (int i = 0 ; i < pointCount ; i++) {
        connectionsFirst[i] = std::vector<int>(pointCount, 0);
        connectionsSecond[i] = std::vector<int>(pointCount, 0);
    }
    int wireCountTmp = wireCount;

    for (int i = 0 ; i < pointCount && wireCountTmp > 0 ; i++)
        for (int j = i + 1 ; j < pointCount && wireCountTmp > 0 ; j++) {
            connectionsFirst[i][j] = 1;
            wireCountTmp--;
        }
    wireCountTmp = wireCount;
    for (int i = 0 ; i < pointCount && wireCountTmp > 0 ; i++)
        for (int j = 0 ; j < i && wireCountTmp ; j++) {
            connectionsSecond[i][j] = 1;
            wireCountTmp--;
        }
    int S1 = 0, S2 = 0;
    for (int i = 0 ; i < pointCount ; i++) {
        for (int j = 0 ; j < pointCount ; j++) {
            D1[i] += connectionsFirst[i][j];
            D2[i] += connectionsSecond[i][j];
        }
        S1 += D1[i] * D1[i];
        S2 += D2[i] * D1[i];
    }
    std::vector<std::vector<int>> *connnectionsMax = nullptr;
    std::vector<int> *DMax = nullptr;
    int SMax;
    if (S1 > S2) {
        connnectionsMax = &connectionsFirst;
        SMax = S1;
        DMax = &D1;
    }
    else {
        connnectionsMax = &connectionsSecond;
        SMax = S2;
        DMax = &D2;
    }
    std::cout << "Sum S: " << SMax << std::endl;
    sort(DMax -> begin(), DMax -> end(), [](int &a, int &b) {return a > b;});
    for_each(DMax -> begin(), DMax -> end(), [](int &a) {std::cout << a << " ";});
    std::cout << std::endl;

    for (int i = 0 ; i < pointCount ; i++) {
        std::cout << i << " connected to: ";
        for (int j = 0 ; j < pointCount ; j++)
            if ((*connnectionsMax)[i][j] == 1)
                std::cout << j << " ";
        std::cout << std::endl;
    }
    return 0;
}