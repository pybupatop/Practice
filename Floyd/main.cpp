#include <iostream>
#include <string.h>
#include <malloc.h>
#include <fstream>

#define INPUT "input.txt"

int **createSquareMatrix(int n) {
    int **M = (int **)malloc(sizeof(int *) * n);
    for (int i = 0 ; i < n ; i++)
        M[i] = (int *)calloc(n, sizeof(n));
    return M;
}

int **copySquareMatrix(int **M, int n) {
    int **newM = new int *[n];
    for (int i = 0 ; i < n ; i++) {
        newM[i] = new int[n];
        memcpy(newM[i], M[i], sizeof(int) * n);
    }
    return newM;
}

void printSquareMatrix(int **G, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0 ; j < n ; j++)
            std::cout << G[i][j] << " ";
        std::cout << std::endl;
    }
}

int **Floyd(int **G, int n) {
    int **M = copySquareMatrix(G, n);
    int **P = createSquareMatrix(n); // parents

    printSquareMatrix(M, n);
    std::cout << std::endl;
    printSquareMatrix(P, n);
    std::cout << std::endl;

    for (int k = 0 ; k < n ; k++) {
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                if (M[i][k] != -1 && M[k][j] != -1 && i != j) {
                    if (M[i][j] == -1 || M[i][k] + M[k][j] < M[i][j]) {
                        M[i][j] = M[i][k] + M[k][j];
                        P[i][j] = k + 1;
                    }
                }
        printSquareMatrix(M, n);
        std::cout << std::endl;
        printSquareMatrix(P, n);
        std::cout << std::endl;
    }
    return M;
}

int main() {
    std::fstream input(INPUT, std::ios::in);
    int n;
    input >> n;

    int **G = createSquareMatrix(n);

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++)
            input >> G[i][j];
    }
    int **F = Floyd(G, n);
    printSquareMatrix(F, n);
}