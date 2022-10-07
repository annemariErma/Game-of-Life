/// Copyright 2022 annemari, charisse
#include <stdio.h>
#include <stdlib.h>

#define NMAX 25  //  widht
#define MMAX 80  //  height

void input(int **pole);
void draw(int **pole);
void neighbors(int **pole);

int main() {
    char x;
    int **pole = malloc(NMAX * sizeof(int*));
    input(pole);
    draw(pole);
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        scanf("%c", &x);
        while ('q' != x) {
            scanf("%c", &x);
            if (' ' == x) {
                neighbors(pole);
                draw(pole);
            }
        }
    }
    //  memory free
    for (int i = 0; i < NMAX; i++) {
        free(pole[i]);
    }
    free(pole);

    return 0;
}

void input(int **pole) {
    // memory allocate
    for (int i = 0; i < NMAX; i++) {
        pole[i] = malloc(MMAX * sizeof(int));
        }
    // scanning
    int kletka;
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX;  j++) {
            scanf("%d", &kletka);
            pole[i][j] = kletka;
        }
    }
}

//  field draw
void draw(int **pole) {
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX;  j++) {
            if (1 == pole[i][j]) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}


void neighbors(int **pole) {  //  преобразование
    // memory allocate future
    int **future = malloc(NMAX * sizeof(int*));
    for (int i = 0; i < NMAX; i++) {
        future[i] = malloc(MMAX * sizeof(int));
    }
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX;  j++) {
            future[i][j] = 0;
        }
    }
    //  проверка соседей
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX;  j++) {
            int village = 0;  // счетчик соседей
            village = pole[(i + 1) % NMAX][(j + 1) % MMAX] + pole[(i + 1) % NMAX][j % MMAX] +
                      pole[(i + 1) % NMAX][(MMAX + j - 1) % MMAX] + pole[i % NMAX][(j + 1) % MMAX] +
                      pole[i % NMAX][(MMAX + j - 1) % MMAX] + pole[(NMAX + i - 1) % NMAX][(j + 1) % MMAX] +
                      pole[(NMAX + i - 1) % NMAX][j % MMAX] +
                      pole[(NMAX + i - 1) % NMAX][(MMAX + j - 1) % MMAX];
            if (0 == pole[i][j] && 3 == village) {
                future[i][j] = 1;
            }
            if (1 == pole[i][j] && (village < 2 || village > 3)) {
                future[i][j] = 0;
            }
            if (1 == pole[i][j] && (2 == village || 3 == village)) {
                future[i][j] = 1;
            }
        }
    }
    // переброс из future в pole
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX;  j++) {
            int tmp;
            tmp = future[i][j];
            pole[i][j] = tmp;
        }
    }
    //  memory free future
    for (int i = 0; i < NMAX; i++) {
        free(future[i]);
    }
    free(future);
}

