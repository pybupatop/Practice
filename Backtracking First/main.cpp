#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <unistd.h>

#define DOMINOS_NUMBER 28
#define NUMBER_OF_POSSIBLE_MOVES 4
#define INPUT "input.txt"

void printMatrix(int **M, int N) {
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < N ; j++)
            std::cout << M[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "--------------------\n";
}

const int dominos[DOMINOS_NUMBER][2] = {
        {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
        {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
        {3, 3}, {3, 4}, {3, 5}, {3, 6},
        {4, 4}, {4, 5}, {4, 6},
        {5, 5}, {5, 6},
        {6, 6}};

const int possibleMoves[NUMBER_OF_POSSIBLE_MOVES][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

bool moveIsPossible(int **moves, int N, const int *move, int posX, int posY) {
    return posX + move[0] >= 0 && posX + move[0] < N &&
           posY + move[1] >= 0 && posY + move[1] < N &&
           moves[posX][posY] == 0 && moves[posX + move[0]][posY + move[1]] == 0;
}

const int *getPossibleMove(int **moves, int N, int posX, int posY) {
    for (int i = 0; i < NUMBER_OF_POSSIBLE_MOVES; i++)
        if (moveIsPossible(moves, N, possibleMoves[i], posX, posY))
            return possibleMoves[i];
    return NULL;
}

int dominoIndex(int firstPart, int secondPart) {
    int ind = 0;
    while (ind < DOMINOS_NUMBER &&
           !(dominos[ind][0] == firstPart && dominos[ind][1] == secondPart ||
             dominos[ind][0] == secondPart && dominos[ind][1] == firstPart))
        ind++;

    return ind;
}

void makeMove(int **moves, const int *move, int posX, int posY, int moveNum = 1) {
    moves[posX][posY] = moveNum;
    moves[posX + move[0]][posY + move[1]] = moveNum;
}

void eraseMove(int **moves, const int *move, int posX, int posY) {
    moves[posX][posY] = 0;
    moves[posX + move[0]][posY + move[1]] = 0;
}

// if true then posX, posY contain new coordinates
bool getNextPosition(int **moves, int N, int &posX, int &posY) {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            if (moves[x][y] == 0) {
                posX = x;
                posY = y;
                return true;
            }
    return false;
}

int getDominoSetsCount(int *dominos) {
    int max = 0;
    for (int i = 0 ; i < DOMINOS_NUMBER ; i++)
        if (dominos[i] > max)
            max = dominos[i];
    return max;
}

int getDominoCount(int *dominos) {
    int count = 0;
    for (int i = 0 ; i < DOMINOS_NUMBER ; i++)
        count += dominos[i];
    return count;
}

void countDominoSetsHelper(int **desk, int N, int *usedDominos, int **moves, int posX, int posY, int &minDominoSetCount) {
    int currentDominoSetCount = getDominoSetsCount(usedDominos);
    if (currentDominoSetCount > minDominoSetCount)
        return;

    int usedDominosCount = getDominoCount(usedDominos);

    // это последнее домино
    if (usedDominosCount == N * N / 2 - 1) {
        // если есть возможный ход, сделать его и вернуть количество затраченных наборов
        const int *possibleMove = getPossibleMove(moves, N, posX, posY);
        if (possibleMove == NULL)
            return;

        int dominoInd = dominoIndex(desk[posX][posY], desk[posX + possibleMove[0]][posY + possibleMove[1]]);
        usedDominos[dominoInd]++;

        makeMove(moves, possibleMove, posX, posY, usedDominosCount + 1);

        int dominoSetCount = getDominoSetsCount(usedDominos);

        std::cout << "Current domino sets count: " << dominoSetCount << std::endl;
        printMatrix(moves, N);

        eraseMove(moves, possibleMove, posX, posY);

        if (dominoSetCount < minDominoSetCount)
            minDominoSetCount = dominoSetCount;

        usedDominos[dominoInd]--;

        return;
    }

    for (int i = 0 ; i < NUMBER_OF_POSSIBLE_MOVES ; i++) {
        // если ход возможен
        if (moveIsPossible(moves, N, possibleMoves[i], posX, posY)) {
            // сделать ход
            makeMove(moves, possibleMoves[i], posX, posY, usedDominosCount + 1);
            int dominoInd = dominoIndex(desk[posX][posY], desk[posX + possibleMoves[i][0]][posY + possibleMoves[i][1]]);
            usedDominos[dominoInd]++;
            // std::cout << "Used domino: [" <<  dominos[dominoInd][0] << "," << dominos[dominoInd][1] << "]\n";
            // printMatrix(moves, N);

            // получить следующую возможную позицию
            int nextX, nextY;
            getNextPosition(moves, N, nextX, nextY);

            // sleep(1);
            countDominoSetsHelper(desk, N, usedDominos, moves, nextX, nextY, minDominoSetCount);

            // стереть ход
            eraseMove(moves, possibleMoves[i], posX, posY);
            usedDominos[dominoInd]--;
        }
    }
}

int countDominoSets(int **desk, int N) {
    int minSetsCount = INT32_MAX;
    int *usedDominos = new int[DOMINOS_NUMBER];
    int **moves = new int *[DOMINOS_NUMBER];
    for (int i = 0 ; i < DOMINOS_NUMBER ; i++) {
        usedDominos[i] = 0;
        moves[i] = new int[DOMINOS_NUMBER];
        memset(moves[i], 0, sizeof(int) * DOMINOS_NUMBER);
    }

    countDominoSetsHelper(desk, N, usedDominos, moves, 0, 0, minSetsCount);

    delete usedDominos;
    for (int i = 0 ; i < DOMINOS_NUMBER ; i++)
        delete moves[i];
    delete moves;

    return minSetsCount;
}

int main() {
    std::fstream fin;
    fin.open(INPUT, std::ios::in);
    if(!fin.is_open()) {
        std::cout << "Ошибка при открытии файла" << std::endl;
        return -1;
    }
    int N;
    fin >> N;
    if (N % 2 == 1) {
        std::cout << "It's impossible" << std::endl;
        return 0;
    }
    int **desk = new int*[N];
    for (int i = 0 ; i < N ; i++) {
        desk[i] = new int[N];
        for (int j = 0 ; j < N ; j++)
            fin >> desk[i][j];
    }
    std::cout << "Desk:\n";
    printMatrix(desk, N);
    int setsCount = countDominoSets(desk, N);
    std::cout << setsCount << std::endl;
}